#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "VectorField.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
    void windowResized(int w, int h);
private:
    // FBO size matches that of Kinect output as a performance test
    const int FBO_WIDTH = 640;
    const int FBO_HEIGHT = 480;
    // number of subdivisions of the the FBO.
    // in this case: 640 / 32 = 20; 480 / 32 = 15;
    const int FIELD_SUBDIVISION = 32;
    
    ofShader mShader;
    ofVec2f mFboPos;
    ofFbo mFbo;
    ofImage mImage;
    VectorField mVectorField = VectorField();
    
    bool mShowGui = false;
    ofxPanel mGui;
    ofParameterGroup mPerlinNoise;
    ofParameter<float> mPerlinOffsetX;
    ofParameter<float> mPerlinOffsetY;
    ofParameter<float> mPerlinScale;
    ofParameter<float> mPerlinSpeed;
};
