#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "object.h"
#include <stdbool.h>
#include <math.h>

double calculateDistance(double x1, double y1, double x2, double y2);

double clamp(double value, double a, double b);

bool checkOverlap(Object *a, Object *b);

bool checkInside(Object *obj, double x, double y);

void getCenter(Object *obj, double *x, double *y);

void getSurroundingRect(Object *obj, Rectangle *resultRect);

#endif