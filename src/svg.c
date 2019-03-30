#include "svg.h"

void putSVGStart(FILE *file) {
    fputs("<svg height=\"1000\" width=\"1000\">\n", file);
}

void putSVGCircle(FILE *file, Circle *circ, char color1[], char color2[]) {
    fprintf(file, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\"/>\n",
            circ->x,
            circ->y,
            circ->radius,
            color1,
            STROKE_WIDTH,
            color2);
}

void putSVGRectangle(FILE *file, Rectangle *rect, char color1[], char color2[]) {
    fprintf(file, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\"/>\n",
            rect->x,
            rect->y,
            rect->width,
            rect->height,
            color1,
            STROKE_WIDTH,
            color2);
}

void putSVGEnd(FILE *file) {
    fputs("</svg>\n", file);
}