#include <string.h>
#include "geometry.h"

bool processGeometry(FILE *entryFile, FILE *outputFile, FILE *outputQryFile, BinaryTree *objectTree) {
    int nx = DEFAULT_MAXIMUM;

    objectTree->numElements = 0;
    objectTree->numMax = nx;
    objectTree->top = NULL;
    //*objectsPtr = malloc(nx * sizeof(Object));
    //Object *objects = *objectsPtr;

    putSVGStart(outputFile);
    if(outputQryFile != NULL)
        putSVGStart(outputQryFile);

    char buffer[128];
    while(fgets(buffer, 128, entryFile) != NULL) {
        char type[16];
        sscanf(buffer, "%15s", type);
        if(strcmp(type, "nx") == 0) {
            sscanf(buffer + 3, "%d", &nx);
            //*objectsPtr = realloc(*objectsPtr, nx * sizeof(Object));
            //objects = *objectsPtr;
            objectTree->numMax = nx;
        } else if(strcmp(type, "c") == 0) {
            int i;
            double radius, x, y;
            char color1[32], color2[32];
            sscanf(buffer + 2, "%d %lf %lf %lf %s %s", &i, &radius, &x, &y, color1, color2);
            Object *o = createCircle(i, radius, x, y);
            if(treeInsert(objectTree, o) == false) {
                printf("Erro: Número máximo de elementos ultrapassado!\n");
                return false;
            }
            putSVGCircle(outputFile, (Circle *) o->content, color1, color2);
            if(outputQryFile != NULL)
                putSVGCircle(outputQryFile, (Circle *) o->content, color1, color2);
        } else if(strcmp(type, "r") == 0) {
            int i;
            double width, height, x, y;
            char color1[32], color2[32];
            sscanf(buffer + 2, "%d %lf %lf %lf %lf %s %s", &i, &width, &height, &x, &y, color1, color2);
            Object *o = createRectangle(i, width, height, x, y);
            if(treeInsert(objectTree, o) == false) {
                printf("Erro: Número máximo de elementos ultrapassado!\n");
                return false;
            }
            putSVGRectangle(outputFile, (Rectangle *) o->content, color1, color2);
            if(outputQryFile != NULL)
                putSVGRectangle(outputQryFile, (Rectangle *) o->content, color1, color2);
        } else if(strcmp(type, "t") == 0) {
            double x, y;
            char text[128];
            sscanf(buffer + 2, "%lf %lf %128[^\n]", &x, &y, text);
            putSVGText(outputFile, x, y, text);
            if(outputQryFile != NULL)
                putSVGText(outputQryFile, x, y, text);
        }
    }

    putSVGEnd(outputFile);

    return true;
}

bool processQuery(FILE *queryFile, FILE *outputFile, FILE *txtFile, BinaryTree *objectTree) {
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
            fputs(buffer, txtFile);
            int idA, idB;
            sscanf(buffer + 3, "%d %d", &idA, &idB);
            Object *a = treeFind(objectTree, idA), *b = treeFind(objectTree, idB);
            bool overlaps = checkOverlap(a, b);
            if(overlaps) {
                fprintf(txtFile, "SIM\n\n");
            } else {
                fprintf(txtFile, "NAO\n\n");
            }
            double extremesA[4];
            getExtremes(a, extremesA);
            double extremesB[4];
            getExtremes(b, extremesB);
            double minX = extremesA[0] < extremesB[0] ? extremesA[0] : extremesB[0];
            double minY = extremesA[1] < extremesB[1] ? extremesA[1] : extremesB[1];
            double maxX = extremesA[2] < extremesB[2] ? extremesB[2] : extremesA[2];
            double maxY = extremesA[3] < extremesB[3] ? extremesB[3] : extremesA[3];
            putSVGBox(outputFile, minX, minY, maxX - minX, maxY - minY, !overlaps);

        } else if(strcmp(type, "i?") == 0) {
            fputs(buffer, txtFile);
            int id;
            double x, y;
            sscanf(buffer + 3, "%d %lf %lf", &id, &x, &y);
            Object* o = treeFind(objectTree, id);
            bool inside = checkInside(o, x, y);
            if(inside) {
                fprintf(txtFile, "SIM\n\n");
            } else {
                fprintf(txtFile, "NAO\n\n");
            }
            double centerX, centerY;
            getCenter(o, &centerX, &centerY);
            putSVGLine(outputFile, centerX, centerY, x, y);
            putSVGPoint(outputFile, x, y, inside);
        } else if(strcmp(type, "d?") == 0) {
            fputs(buffer, txtFile);
            int j, k;
            sscanf(buffer + 3, "%d %d", &j, &k);
            double c1x, c1y, c2x, c2y;
            getCenter(treeFind(objectTree, j), &c1x, &c1y);
            getCenter(treeFind(objectTree, k), &c2x, &c2y);
            double dist = calculateDistance(c1x, c1y, c2x, c2y);
            fprintf(txtFile, "%lf\n\n", dist);
            putSVGLine(outputFile, c1x, c1y, c2x, c2y);
            char distText[16];
            sprintf(distText, "%lf", dist);
            putSVGText(outputFile, c1x + (c2x - c1x) / 2, c1y + (c2y - c1y) / 2, distText);
        } else if(strcmp(type, "bb") == 0) {

        }
    }
    putSVGEnd(outputFile);
}