#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef enum ObjectType {
    OBJ_CIRC,
    OBJ_RECT
} ObjectType;

typedef struct Object {
    void *content;
    ObjectType type;
    int id;
    char color1[24], color2[24];
} Object;

typedef struct Circle {
    double x, y, radius;
} Circle;

typedef struct Rectangle {
    double x, y, width, height;
} Rectangle;

Object *createCircle(int id, double radius, double x, double y, char color1[], char color2[]);

Object *createRectangle(int id, double width, double height, double x, double y, char color1[], char color2[]);

void destroyObject(Object *obj);

#endif