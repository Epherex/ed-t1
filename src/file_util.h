#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

FILE *openFile(char *baseDir, char *path, char *flags);

void changeExtension(char *filePath, char *newExtension);

void putSVGStart(FILE *file);

#endif