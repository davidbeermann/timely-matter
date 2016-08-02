#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void windowResized(int w, int h);
private:
    const int FBO_WIDTH = 800;
    const int FBO_HEIGHT = 600;
    ofShader mShader;
    ofVec2f mFboPos;
    ofFbo mFbo;
    ofxPanel mGui;
    ofParameter<float> mGuiOffsetX;
    ofParameter<float> mGuiOffsetY;
    ofParameter<float> mGuiScale;
    ofParameter<float> mGuiSpeed;
};
