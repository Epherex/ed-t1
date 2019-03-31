#include "geometry.h"

double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double clamp(double value, double a, double b) {
	double clamped = value > b ? b : value;
	clamped = value < a ? a : clamped;
	return clamped;
}

bool checkOverlap(Object *a, Object *b) {
    if(a->type == OBJ_CIRC && b->type == OBJ_CIRC) {
        Circle *c1 = (Circle *) a->content;
        Circle *c2 = (Circle *) b->content;
        double dist = calculateDistance(c1->x, c1->y, c2->x, c2->y);
        return (dist < c1->radius + c2->radius);
    } else if(a->type == OBJ_RECT && b->type == OBJ_RECT) {
        Rectangle *r1 = (Rectangle *) a->content;
        Rectangle *r2 = (Rectangle *) b->content;
        return r1->x < r2->x + r2->width &&
               r1->x + r1->width > r2->x &&
               r1->y < r2->y + r2->height &&
               r1->y + r1->height > r2->y;
    } else {
        // Deixar o a como círculo e b como retângulo
        if(a->type == OBJ_RECT) {
            Object *temp = a;
            a = b;
            b = temp;
        }
        Circle *circ = (Circle *) a->content;
        Rectangle *rect = (Rectangle *) b->content;

        double nearestX = clamp(circ->x, rect->x, rect->x + rect->width);
        double nearestY = clamp(circ->y, rect->y, rect->y + rect->height);

        double dist = calculateDistance(nearestX, nearestY, circ->x, circ->y);

        return dist < circ->radius;
    }
}

bool checkInside(Object *obj, double x, double y) {
    if(obj->type == OBJ_CIRC) {
        Circle *circ = (Circle *) obj->content;
        return calculateDistance(x, y, circ->x, circ->y) < circ->radius;
    } else {
        Rectangle *rect = (Rectangle *) obj->content;
        return x > rect->x && x < rect->x + rect->width && y > rect->y && y < rect->y + rect->height;
    }
}

void getCenter(Object *obj, double *x, double *y) {
    if(obj->type == OBJ_CIRC) {
        Circle *circ = (Circle *) obj->content;
        *x = circ->x;
        *y = circ->y;
    } else {
        Rectangle *rect = (Rectangle *) obj->content;
        *x = rect->x + rect->width/2;
        *y = rect->y + rect->height/2;
    }
}

void getSurroundingRect(Object *obj, Rectangle *resultRect) {
    if(obj->type == OBJ_CIRC) {
        Circle *circ = (Circle *) obj->content;
        resultRect->x = circ->x - circ->radius;
        resultRect->y = circ->y - circ->radius;
        resultRect->width = circ->radius * 2;
        resultRect->height = circ->radius * 2;
    } else {
        Rectangle *rect = (Rectangle *) obj->content;
        resultRect->x = rect->x;
        resultRect->y = rect->y;
        resultRect->width = rect->width;
        resultRect->height = rect->height;
    }
}