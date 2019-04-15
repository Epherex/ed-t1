#include "tree.h"

bool treeInsert(BinaryTree *tree, Object *obj) {
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
            if(obj->id > current->obj->id) {
                previous = current;
                current = current->right;
            } else if(obj->id < current->obj->id) {
                previous = current;
                current = current->left;
            } else {
                newNode->right = current->right;
                newNode->left = current->left;
                if(current == tree->top) {
                    tree->top = newNode;
                }
                destroyObject(current->obj);
                free(current);
                break;
            }
        }
        if(obj->id > previous->obj->id) {
            previous->right = newNode;
        } else {
            previous->left = newNode;
        }
    }
    return tree->numElements <= tree->numMax;
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

void nodeExecute(Node *node, void (*f)(Object*, void*), void *arg) {
    if(node != NULL) {
        nodeExecute(node->left, f, arg);
        (*f)(node->obj, arg);
        nodeExecute(node->right, f, arg);
    }
}

void treeExecute(BinaryTree *tree, void (*f)(Object*, void*), void *arg) {
    Node *node = tree->top;
    nodeExecute(node, f, arg);
}

void nodeDestroy(Node *node) {
    if(node != NULL) {
        nodeDestroy(node->left);
        nodeDestroy(node->right);
        destroyObject(node->obj);
        free(node);
    }
}

void treeDestroy(BinaryTree *tree) {
    nodeDestroy(tree->top);
}