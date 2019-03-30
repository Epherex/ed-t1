#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdio.h>
#include "object.h"
#include "tree.h"
#include "svg.h"

#define DEFAULT_MAXIMUM 1000

bool processGeometry(FILE *entryFile, FILE *outputFile, BinaryTree *objectTree);

#endif