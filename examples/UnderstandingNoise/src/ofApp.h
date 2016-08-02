#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
private:
    ofRectangle rectStatic;
    ofRectangle rectAnimated;
    ofRectangle rectTime;
    float animSpeed = 0.01f;
    float animOffset = 0.f;
    float timeScale = 0.001f;
    float timeOffset = 0.f;
};
