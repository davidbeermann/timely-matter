#include "Line.h"

Line::Line(float x1, float y1, float x2, float y2) {
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
}

void Line::draw() {
    ofDrawLine(p1, p2);
}