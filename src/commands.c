#include <string.h>
#include "commands.h"
#include "file_util.h"

bool processGeometry(FILE *entryFile, FILE *outputFile, FILE *outputQryFile, BinaryTree *objectTree) {
    int nx = DEFAULT_MAXIMUM;

    objectTree->numElements = 0;
    objectTree->numMax = nx;
    objectTree->top = NULL;

    putSVGStart(outputFile);
    if(outputQryFile != NULL)
        putSVGStart(outputQryFile);

    char buffer[128];
    while(fgets(buffer, 100, entryFile) != NULL) {
        char type[16];
        sscanf(buffer, "%15s", type);
        if(strcmp(type, "nx") == 0) {
            sscanf(buffer + 3, "%d", &nx);
            objectTree->numMax = nx;
        } else if(strcmp(type, "c") == 0) {
            int i;
            double radius, x, y;
            char color1[32], color2[32];
            sscanf(buffer + 2, "%d %lf %lf %lf %s %s", &i, &radius, &x, &y, color1, color2);
            Object *o = createCircle(i, radius, x, y, color1, color2);
            if(treeInsert(objectTree, o) == false) {
                #ifdef __DEBUG__
                printf("Erro: Número máximo de elementos ultrapassado!\n");
                #endif
            }
            putSVGCircle(outputFile, (Circle *) o->content, color1, color2);
            if(outputQryFile != NULL)
                putSVGCircle(outputQryFile, (Circle *) o->content, color1, color2);
        } else if(strcmp(type, "r") == 0) {
            int i;
            double width, height, x, y;
            char color1[32], color2[32];
            sscanf(buffer + 2, "%d %lf %lf %lf %lf %s %s", &i, &width, &height, &x, &y, color1, color2);
            Object *o = createRectangle(i, width, height, x, y, color1, color2);
            if(treeInsert(objectTree, o) == false) {
                #ifdef __DEBUG__
                printf("Erro: Número máximo de elementos ultrapassado!\n");
                #endif
            }
            putSVGRectangle(outputFile, (Rectangle *) o->content, color1, color2);
            if(outputQryFile != NULL)
                putSVGRectangle(outputQryFile, (Rectangle *) o->content, color1, color2);
        } else if(strcmp(type, "t") == 0) {
            double x, y;
            char text[128];
            sscanf(buffer + 2, "%lf %lf %128[^\n]", &x, &y, text);
            putSVGText(outputFile, x, y, text);
            //if(outputQryFile != NULL)
            //    putSVGText(outputQryFile, x, y, text);
        }
    }
    putSVGEnd(outputFile);
    return true;
}

void insertSVG(Object* o, void *parametersVoid) {
    BBParameters *params = (BBParameters*) parametersVoid;
    FILE *file = params->file;
    if(o->type == OBJ_CIRC) {
        putSVGCircle(file, o->content, o->color1, o->color2);
        Rectangle surroundingRect;
        getSurroundingRect(o, &surroundingRect);
        putSVGRectangle(file, &surroundingRect, params->color, "none");
    } else {
        putSVGRectangle(file, o->content, o->color1, o->color2);
        Rectangle *rect = o->content;
        double cx, cy;
        getCenter(o, &cx, &cy);
        double rx = rect->width/2, ry = rect->height/2;
        putSVGEllipse(file, cx, cy, rx, ry, params->color, "none");
    }
}

bool processQuery(FILE *queryFile, FILE *outputFile, FILE *txtFile, BinaryTree *objectTree, char outputDir[], char svgFileName[]) {
    char buffer[128];
    while(fgets(buffer, 128, queryFile) != NULL) {
        int len = strlen(buffer);
        if(buffer[len - 1] != '\n') {
            buffer[len] = '\n';
            buffer[len + 1] = '\0';
        }
        char type[16];
        sscanf(buffer, "%15s", type);
        if(strcmp(type, "o?") == 0) {
            int idA, idB;
            sscanf(buffer + 3, "%d %d", &idA, &idB);
            Object *a = treeFind(objectTree, idA), *b = treeFind(objectTree, idB);
            if(a == NULL || b == NULL) {
                printf("Erro: Elemento não encontrado!\n");
                return false;
            }
            fputs(buffer, txtFile);
            bool overlaps = checkOverlap(a, b);
            if(overlaps) {
                fprintf(txtFile, "SIM\n\n");
            } else {
                fprintf(txtFile, "NAO\n\n");
            }
            Rectangle rectA;
            getSurroundingRect(a, &rectA);
            Rectangle rectB;
            getSurroundingRect(b, &rectB);
            double minX = rectA.x < rectB.x ? rectA.x : rectB.x;
            double minY = rectA.y < rectB.y ? rectA.y : rectB.y;
            double maxX = rectA.x + rectA.width < rectB.x + rectB.width ? rectB.x + rectB.width : rectA.x + rectA.width;
            double maxY = rectA.y + rectA.height < rectB.y + rectB.height ? rectB.y + rectB.height : rectA.y + rectA.height;
            putSVGBox(outputFile, minX, minY, maxX - minX, maxY - minY, !overlaps);
        } else if(strcmp(type, "i?") == 0) {
            int id;
            double x, y;
            sscanf(buffer + 3, "%d %lf %lf", &id, &x, &y);
            Object* o = treeFind(objectTree, id);
            if(o == NULL) {
                printf("Erro: Elemento não encontrado!\n");
                return false;
            }
            fputs(buffer, txtFile);
            bool inside = checkInside(o, x, y);
            if(inside) {
                fprintf(txtFile, "INTERNO\n\n");
            } else {
                fprintf(txtFile, "NAO INTERNO\n\n");
            }
            double centerX, centerY;
            getCenter(o, &centerX, &centerY);
            putSVGLine(outputFile, centerX, centerY, x, y);
            putSVGPoint(outputFile, x, y, inside);
        } else if(strcmp(type, "d?") == 0) {
            int j, k;
            sscanf(buffer + 3, "%d %d", &j, &k);
            double c1x, c1y, c2x, c2y;
            Object *a = treeFind(objectTree, j), *b = treeFind(objectTree, k);
            if(a == NULL || b == NULL) {
                printf("Erro: Elemento não encontrado!\n");
                return false;
            }
            getCenter(a, &c1x, &c1y);
            getCenter(b, &c2x, &c2y);
            double dist = calculateDistance(c1x, c1y, c2x, c2y);
            fputs(buffer, txtFile);
            fprintf(txtFile, "%lf\n\n", dist);
            putSVGLine(outputFile, c1x, c1y, c2x, c2y);
            char distText[16];
            sprintf(distText, "%lf", dist);
            putSVGText(outputFile, c1x + (c2x - c1x) / 2, c1y + (c2y - c1y) / 2, distText);
        } else if(strcmp(type, "bb") == 0) {
            char nameWithSuffix[128];
            strcpy(nameWithSuffix, svgFileName);
            char suffix[32], color[16];
            sscanf(buffer + 3, "%s %s", suffix, color);
            addSuffix(nameWithSuffix, suffix);
            FILE *bbFile = openFile(outputDir, nameWithSuffix, "w");
            if(bbFile == NULL) {
                return false;
            }
            putSVGStart(bbFile);
            BBParameters params = {bbFile, color};
            treeExecute(objectTree, insertSVG, &params);
            putSVGEnd(bbFile);
            fclose(bbFile);
        }
    }
    putSVGEnd(outputFile);
    return true;
}