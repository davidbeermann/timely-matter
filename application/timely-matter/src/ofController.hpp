#pragma once

#include "ofMain.h"
#include "ofApp.h"


class ofController : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    shared_ptr<ofApp> mainApp;
};