#include "ofApp.h"


void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(33);
    
    mInputProvider->setup();
    
//    mFbo.setup(KINECT_CAM_WIDTH, KINECT_CAM_HEIGHT);
    
    mVectorField.setup(KINECT_CAM_WIDTH, KINECT_CAM_HEIGHT, 32);
    mFieldMaxStrength = 8.0f;
    
    mParticleSystem.setup(50, ofVec3f(KINECT_CAM_WIDTH, KINECT_CAM_HEIGHT, 0.f));
    
    // setup GUI
    mGui.setDefaultWidth(250);
    mGui.setWidthElements(250);
    mGui.setup("Timely Matter Controls");
//    mGui.add(mFbo.getGuiParams());
    mGui.add(mInputProvider->getGuiParams());
    mGui.add(mVectorField.getGuiParams());
    mGui.add(mParticleSystem.getGuiParams());
    mGui.loadFromFile("settings.xml");
    mShowGui = false;
    
    // set initial centered position
    windowResized(ofGetWidth(), ofGetHeight());
}


void ofApp::update() {
    // update FBO first ...
    mInputProvider->update();
//    mFbo.update();
    // ... before retrieving pixel data to update vector field.
    mVectorField.update(mInputProvider->getPixels(), mFieldMaxStrength);
//    mVectorField.update(mFbo.getPixels(), mFieldMaxStrength);
    
    mParticleSystem.applyVectorField(mVectorField);
    mParticleSystem.update();
}


void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(mCenteredPos);
    
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(0, 0, KINECT_CAM_WIDTH, KINECT_CAM_HEIGHT);
    ofPopStyle();
    
//    mFbo.draw();
    mInputProvider->draw();
    mVectorField.draw();
    mParticleSystem.draw(mVectorField);
    
    ofPopMatrix();
    
    // define debug info string
    string debugInfo = "FPS " + to_string((int) ofGetFrameRate());
    debugInfo += "\nPress 'g' to toggle GUI display";
    
    // show debug info
    ofDrawBitmapString(debugInfo, 10, 20);
    
    if (mShowGui) {
        mGui.draw();
    }
}


void ofApp::keyPressed(int key) {
    switch (key) {
        case 'g':
            if (!mShowGui) {
                float x = (((ofGetWidth() - KINECT_CAM_WIDTH) / 2.f) - mGui.getWidth()) / 2.f;
                float y = (ofGetHeight() - mGui.getHeight()) / 2.f;
                mGui.setPosition(x, y);
            }
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
