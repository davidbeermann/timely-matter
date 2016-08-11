#include "ofApp.h"


void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(33);
    
    mFbo.setup(KINECT_CAM_WIDTH, KINECT_CAM_HEIGHT);
    
    // setup GUI
    mGui.setup("Timely Matter Controls");
    mGui.add(mFbo.getGuiParams());
    mShowGui = false;
    
    // set initial centered position
    windowResized(ofGetWidth(), ofGetHeight());
}


void ofApp::update() {
    mFbo.update();
}


void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(mCenteredPos);
    
    mFbo.draw();
    
    ofPopMatrix();
    
    // define debug info string
    string debugInfo = "FPS " + to_string((int) ofGetFrameRate());
    debugInfo += "\nPress 'g' to toggle GUI";
    
    // show debug info
    ofDrawBitmapString(debugInfo, 10, 20);
    
    if (mShowGui) {
        mGui.draw();
    }
}


void ofApp::keyPressed(int key) {
    switch (key) {
        case 'g':
            // toggle gui display
            mShowGui = !mShowGui;
            break;
        default:
            break;
    }
}


void ofApp::windowResized(int w, int h) {
    mCenteredPos.set((w - KINECT_CAM_WIDTH) * 0.5f, (h - KINECT_CAM_HEIGHT) * 0.5f);
}
