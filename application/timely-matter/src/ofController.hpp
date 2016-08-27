#pragma once

#include "ofMain.h"
#include "ofApp.h"
#include "ofxGui.h"
#include "AppVars.hpp"


class ofController : public ofBaseApp {
    
    void m_drawModeSelectionView();
    void m_evalModeSelectionInput(int selection);
    void m_setupMode();
    void m_updateGuiParams();
    
    AppState m_state;
    AppMode m_mode;
    ofxPanel m_gui;
    bool m_gui_visible;
    string m_debug_info;
    
public:
    
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
    
    shared_ptr<ofApp> app_sptr;
};