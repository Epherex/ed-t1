#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include "object.h"
#include "tree.h"
#include "svg.h"
#include "geometry.h"

#define DEFAULT_MAXIMUM 1000

typedef struct BBParameters {
    FILE *file;
    char *color;
} BBParameters;

bool processGeometry(FILE *entryFile, FILE *outputFile, FILE *outputQryFile, BinaryTree *objectTree);

bool processQuery(FILE *queryFile, FILE *outputFile, FILE *txtFile, BinaryTree *objectTree, char outputDir[], char svgFileName[]);

#endif