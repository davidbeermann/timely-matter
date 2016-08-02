#include "ofApp.h"


void ofApp::setup() {
    ofSetFrameRate(30);
    
    // setup rectangle areas to draw the perlin noise graphs into
    int padding = 20;
    int height = 200;
    rectStatic = ofRectangle(padding, padding, ofGetWidth() - 2 * padding, height);
    rectAnimated = ofRectangle(padding, height + padding * 2, ofGetWidth() - 2 * padding, height);
    rectTime = ofRectangle(padding, height * 2 + padding * 3, ofGetWidth() - 2 * padding, height);
}


void ofApp::update() {
    // update offset values
    animOffset += animSpeed;
    timeOffset += ofGetElapsedTimef() * timeScale;
}


void ofApp::draw() {
    // draw rectangles to stage
    ofSetColor(255);
    ofDrawRectangle(rectStatic);
    ofDrawRectangle(rectAnimated);
    ofDrawRectangle(rectTime);
    
    ofSetColor(33);
    
    // draw static noise graph
    for(int i = (int) rectStatic.x; i < rectStatic.getRight(); ++i) {
        ofDrawLine(i, rectStatic.getBottom(), i, ofNoise(i*0.01f) * rectStatic.height);
    }
    
    // draw continuously animated noise graph
    for(int i = (int) rectAnimated.x; i < rectAnimated.getRight(); ++i) {
        ofDrawLine(i, rectAnimated.getBottom(), i, rectAnimated.getBottom() - ofNoise(animOffset + i * animSpeed) * rectAnimated.height);
    }
    
    // draw noise graph based on elapsed time
    float time = ofGetElapsedTimef() * timeScale;
    for (int i = 0; i < rectTime.width; ++i) {
        float x = rectTime.getLeft() + i;
        ofDrawLine(x, rectTime.getBottom(), x, rectTime.getBottom() - ofNoise(timeOffset+i*time) * rectTime.height);
    }
}