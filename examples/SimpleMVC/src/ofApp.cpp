#include "ofApp.h"
#include "AppModel.hpp"


void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(33);
    
    // setup manager for views
    m_view_manager.setup();
    
    // app command mapping
    ofAddListener(m_events.change_state, &m_change_state_cmd, &ChangeStateCommand::execute);
    
    // set initial state
    AppState state = AppState::INTRO;
    ofNotifyEvent(m_events.change_state, state, this);
    ofNotifyEvent(m_events.change_state, state, this); // to be neglected!
}

//--------------------------------------------------------------
void ofApp::update() {
    m_view_manager.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    m_view_manager.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
