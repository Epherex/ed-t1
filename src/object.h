#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>
#include <math.h>

typedef enum ObjectType {
    OBJ_CIRC,
    OBJ_RECT
} ObjectType;

typedef struct Object {
    void *content;
    ObjectType type;
    int id;
} Object;

typedef struct Circle {
    double x, y, radius;
} Circle;

typedef struct Rectangle {
    double x, y, width, height;
} Rectangle;

Object *createCircle(int id, double radius, double x, double y);

Object *createRectangle(int id, double width, double height, double x, double y);

void destroyObject(Object *obj);

double calculateDistance(double x1, double y1, double x2, double y2);

double clamp(double value, double a, double b);

bool checkOverlap(Object *a, Object *b);

bool checkInside(Object *obj, double x, double y);

void getCenter(Object *obj, double *x, double *y);

void getExtremes(Object *obj, double *values);

#endif