#ifndef OBJECT_H
#define OBJECT_H

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

#endif