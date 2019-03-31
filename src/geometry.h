#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdio.h>
#include "object.h"
#include "tree.h"
#include "svg.h"
#include <math.h>

#define DEFAULT_MAXIMUM 1000

bool processGeometry(FILE *entryFile, FILE *outputFile, FILE *outputQryFile, BinaryTree *objectTree);

bool processQuery(FILE *queryFile, FILE *outputFile, FILE *txtFile, BinaryTree *objectTree);

#endif