#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "object.h"

#define STROKE_WIDTH "3"

void putSVGStart(FILE *file);

void putSVGCircle(FILE *file, Circle *circ, char color1[], char color2[]);

void putSVGRectangle(FILE *file, Rectangle *rect, char color1[], char color2[]);

void putSVGEnd(FILE *file);

#endif