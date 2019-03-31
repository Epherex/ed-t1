#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "object.h"

typedef struct Node {
    struct Node *left, *right;
    Object *obj;
} Node;

typedef struct BinaryTree {
    Node *top;
    int numElements, numMax;
} BinaryTree;

bool treeInsert(BinaryTree *tree, Object *obj);

Object *treeFind(BinaryTree *tree, int id);

#endif