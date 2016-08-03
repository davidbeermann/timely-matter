#include "ofApp.h"


void ofApp::setup(){
    
    // Kinect method signature: init(bool infrared, bool video, bool texture)
    // enable Kinect eith infrared video and texture
    mKinect.init(false, false, true);
    
    // uses some cpu - scews the video image?!
    //mKinect.setRegistration(true);
    
    // setup vector field
    mVectorField.setup(mKinect.getWidth(), mKinect.getHeight(), 32);
    
    // setup GUI to control Kinect
    mKinectParams.setName("Kinect");
    mKinectParams.add(mKinectNear.set("depth near", 500, 500, 1000));
    mKinectParams.add(mKinectFar.set("depth far", 1500, 1000, 2500));
    
    mGui.setup("Parameters");
    mGui.add(mKinectParams);
    mGui.add(mVectorField.getGuiParams());
    
    // set initial positions in window
    windowResized(ofGetWidth(), ofGetHeight());
    
    // open connection to Kinect and start grabbing images
    mKinect.open();
}


void ofApp::update(){
    // set window title with current fps
    ofSetWindowTitle("Configuring Kinect - FPS " + to_string((int) ofGetFrameRate()));
    
    // set depth clipping
    // the closer the range the better results for the texture gray values between 0-255.
    mKinect.setDepthClipping(mKinectNear, mKinectFar);
    
    // update Kinect - grab new camera data
    mKinect.update();
    
    // update vector field
    if(mKinect.isFrameNewDepth()) {
        mVectorField.update(mKinect.getDepthPixels(), 20.f);
    }
}


void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(mTexPos);
    
    // draw texture to stage
    mKinect.drawDepth(0, 0);
    // draw vector field - in case any debug flag is set
    mVectorField.draw();
    
    ofPopMatrix();
    
    mGui.draw();
}


void ofApp::windowResized(int w, int h){
    mTexPos.x = (float) (w - mKinect.getWidth()) * 0.5f;
    mTexPos.y = (float) (h - mKinect.getHeight()) * 0.5f;
}

