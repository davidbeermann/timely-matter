#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
private:
    ofImage mImage;
    ofPoint mPixelPosition;
    ofPoint mImagePosition;
};
