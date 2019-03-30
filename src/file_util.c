#include "file_util.h"

FILE *openFile(char *baseDir, char *path, char *flags) {
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
    FILE *newFile = fopen(fullPath, flags);
    if(newFile == NULL) {
        char stringErro[128];
        sprintf(stringErro, "Erro ao ler arquivo '%s'", fullPath);
        perror(stringErro);
    }
    return newFile;
}

void changeExtension(char *filePath, char *newExtension) {
    int index = strlen(filePath) - 1;

    while(index >= 0 && filePath[index] != '.')
        index--;
    
    if(index < 0)
        sprintf(filePath, "%s.%s", filePath, newExtension);
    else
        strcpy(filePath + index + 1, newExtension);
}