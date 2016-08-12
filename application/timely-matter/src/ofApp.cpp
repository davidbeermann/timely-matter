#include "ofApp.h"


void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(33);
    
    mFbo.setup(KINECT_CAM_WIDTH, KINECT_CAM_HEIGHT);
    
    mVectorField.setup(KINECT_CAM_WIDTH, KINECT_CAM_HEIGHT, 32);
    mFieldMaxStrength = 8.0f;
    mShowField = true;
    
    mParticleSystem.setup(1, ofVec3f(KINECT_CAM_WIDTH, KINECT_CAM_HEIGHT, 0.f));
    
    // setup GUI
    mGui.setup("Timely Matter Controls");
    mGui.add(mFbo.getGuiParams());
    mGui.add(mVectorField.getGuiParams());
    mShowGui = false;
    
    // set initial centered position
    windowResized(ofGetWidth(), ofGetHeight());
}


void ofApp::update() {
    // uupdate FBO first ...
    mFbo.update();
    // ... before retrieving pixel data to update vector field.
    mVectorField.update(mFbo.getPixels(), mFieldMaxStrength);
    
    mParticleSystem.applyVectorField(mVectorField);
    mParticleSystem.update();
}


void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(mCenteredPos);
    
    mFbo.draw();
    
    if (mShowField) {
        mVectorField.draw();
    }
    
    mParticleSystem.draw();
    
    ofPopMatrix();
    
    // define debug info string
    string debugInfo = "FPS " + to_string((int) ofGetFrameRate());
    debugInfo += "\nPress 'g' to toggle GUI display";
    debugInfo += "\nPress 'f' to toggle Vector Field drawing";
    
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
        case 'f':
            // toggle vector field display
            mShowField = !mShowField;
        default:
            break;
    }
}


void ofApp::windowResized(int w, int h) {
    mCenteredPos.set((w - KINECT_CAM_WIDTH) * 0.5f, (h - KINECT_CAM_HEIGHT) * 0.5f);
}
