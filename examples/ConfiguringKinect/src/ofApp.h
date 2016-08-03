#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "VectorField.h"

class ofApp : public ofBaseApp {
    ofxKinect mKinect;
    ofVec2f mTexPos;
    ofxPanel mGui;
    ofParameterGroup mKinectParams;
    ofParameter<int> mKinectNear;
    ofParameter<int> mKinectFar;
    VectorField mVectorField;
public:
    void setup();
    void update();
    void draw();
    void windowResized(int w, int h);
};
