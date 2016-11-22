#include "ofApp.h"

#define PADDING 30


void ofApp::reset() {
    
    m_rect.set(PADDING, PADDING, 0, 0);
    m_color.set(0, ofRandom(255.f), ofRandom(255.f));
    
    m_start = 0.f;
    m_end = 0.f;
    m_progress = 0.f;
    
    m_animating = false;
    m_running = false;

}


void ofApp::setup() {
    
    ofBackground(33);
    
    func_w = ofxeasing::exp::easeInOut;
    func_h = ofxeasing::circ::easeInOut;
    func_r = ofxeasing::sine::easeOut;
    
    reset();
    
}


void ofApp::update() {
    
    if (m_animating) {
    
        float t = ofGetElapsedTimef();
        
        if (t > m_start && !m_running) {
            m_running = true;
            ofLog() << "animation started: " << ofGetElapsedTimef();
        }
        
        if (m_running) {
            m_progress = (t - m_start) / (m_end - m_start);
            
            if (m_progress > 1.f) {
                m_progress = 1.f;
                m_animating = false;
                m_running = false;
                ofLog() << "animation complete: " << ofGetElapsedTimef();
            }
            
            float mw = (float) ofGetWidth() - PADDING * 2.f;
            float w = ofxeasing::map(m_progress, 0.f, 1.f, 0.f, mw, func_w);
            m_rect.setWidth(w);
            
            float mh = (float) ofGetHeight() - PADDING * 2.f;
            float h = ofxeasing::map(m_progress, 0.f, 1.f, 0.f, mh, func_h);
            m_rect.setHeight(h);
            
            float r = ofxeasing::map(m_progress, 0.f, 1.f, 0.f, 255.f, func_r);
            m_color.r = r;
        }
    
    }

}


void ofApp::draw() {
    
    string msg = "Duration in s: " + to_string(m_duration);
    msg += " - Delay in s: " + to_string(m_delay);
    msg += " - animating: " + to_string(m_animating);
    msg += " - running: " + to_string(m_running);
    msg += " - Click anywhere to start animation";
    
    ofSetColor(255);
    ofDrawBitmapString(msg, PADDING, 21);
    
    ofSetColor(m_color);
    ofDrawRectangle(m_rect);
    
}


void ofApp::mouseMoved(int x, int y ) {
    
    m_duration = ofMap(x, 0.f, ofGetWidth(), 0.f, 5.f);
    m_delay = ofMap(y, 0.f, ofGetHeight(), 0.f, 2.f);

}


void ofApp::mousePressed(int x, int y, int button) {

    reset();
    
    m_start = ofGetElapsedTimef() + m_delay;
    m_end = m_start + m_duration;
    m_progress = 0.f;
    
    m_animating = true;
    
}

