#pragma once

#include "ofMain.h"

class Line {
public:
    Line(float x1, float y1, float x2, float y2);
    void draw();
private:
    ofVec2f p1, p2;
};
