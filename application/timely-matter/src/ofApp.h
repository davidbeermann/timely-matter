#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "PerlinNoiseFbo.h"

class ofApp : public ofBaseApp {
    const unsigned int KINECT_CAM_WIDTH = 640;
    const unsigned int KINECT_CAM_HEIGHT = 480;
    ofVec2f mCenteredPos;
    bool mShowGui;
    ofxPanel mGui;
    PerlinNoiseFbo mFbo;
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
};
