#include "tree.h"

bool treeInsert(BinaryTree *tree, Object *obj) {
    if(tree->numElements >= tree->numMax) {
        return false;
    }
    tree->numElements++;
    Node *newNode = malloc(sizeof(Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->obj = obj;
    if(tree->top == NULL) {
        tree->top = newNode;
    } else {
        Node *current = tree->top;
        Node *previous = NULL;
        while(current != NULL) {
            previous = current;
            if(obj->id > current->obj->id) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        if(obj->id > previous->obj->id) {
            previous->right = newNode;
        } else {
            previous->left = newNode;
        }
    }
    return true;
}

Object *treeFind(BinaryTree *tree, int id) {
    Node *current = tree->top;
    while(current != NULL) {
        if(current->obj->id == id) {
            return current->obj;
        } else if(id > current->obj->id) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return NULL;
}