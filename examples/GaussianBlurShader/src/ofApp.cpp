#include "ofApp.h"

#define BUFFER_WIDTH 300
#define BUFFER_HEIGHT 300


void ofApp::setup() {
    ofSetFrameRate(1000);
    ofSetBackgroundColor(20.f);
    
    m_post_fx_queue.init(BUFFER_WIDTH, BUFFER_HEIGHT);
    m_post_fx_queue.add(m_mesh_module);
    m_post_fx_queue.add(m_blur_module);
    
    m_gui.setup("Parameters");
    m_gui.add(m_mesh_module.getParams());
    m_gui.add(m_blur_module.getParams());
}


void ofApp::update() {
    m_post_fx_queue.clear();
    
    m_post_fx_queue.getOutput().begin();
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(0, 0, BUFFER_WIDTH, BUFFER_HEIGHT);
    ofTranslate(BUFFER_WIDTH / 4, BUFFER_HEIGHT / 4);
    ofSetColor(33);
    ofDrawRectangle(0, 0, BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2);
    ofPopStyle();
    ofPopMatrix();
    m_post_fx_queue.getOutput().end();
    
    m_post_fx_queue.render();
}


void ofApp::draw() {
    ofDrawBitmapString("FPS:" + to_string((int)ofGetFrameRate()), 10, 21);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(ofGetElapsedTimef() * 12);
    ofTranslate(-BUFFER_WIDTH/2, -BUFFER_HEIGHT/2);
    m_post_fx_queue.getOutput().draw(0,0);
    ofPopMatrix();
    
    m_gui.draw();
}

