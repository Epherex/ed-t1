#include <string.h>
#include "geometry.h"

bool processGeometry(FILE *entryFile, FILE *outputFile, BinaryTree *objectTree) {
    int nx = DEFAULT_MAXIMUM;

    objectTree->numElements = 0;
    objectTree->numMax = nx;
    objectTree->top = NULL;
    //*objectsPtr = malloc(nx * sizeof(Object));
    //Object *objects = *objectsPtr;

    putSVGStart(outputFile);

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
            // TODO: Inserir no .svg
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
            // TODO: Inserir no .svg
        } else if(strcmp(type, "t") == 0) {
            double x, y;
            char text[128];
            sscanf(buffer + 2, "%lf %lf %128[^\n]", &x, &y, text);
            
        }
    }

    putSVGEnd(outputFile);

    
}