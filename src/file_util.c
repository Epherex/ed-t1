#include "file_util.h"

FILE *openFile(char *baseDir, char *path) {
    char *fullPath;
    int len = strlen(path) + 2;
    if(baseDir != NULL)
        len += strlen(baseDir);
    fullPath = malloc(len * sizeof(char));
    if(baseDir != NULL) {
        if(baseDir[strlen(baseDir) - 1] == '/') {
            sprintf(fullPath, "%s%s", baseDir, path);
        } else {
            sprintf(fullPath, "%s/%s", baseDir, path);
        }
    } else {
        strcpy(fullPath, path);
    }
    printf("%s\n", fullPath);
    FILE *newFile = fopen(fullPath, "r");
    if(newFile == NULL) {
        perror("Erro ao ler arquivo");
        exit(1);
    }
    return newFile;
}