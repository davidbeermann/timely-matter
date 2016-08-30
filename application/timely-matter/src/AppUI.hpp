#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxGui.h"
#include "AppVars.hpp"


class AppUI {
    
    void m_drawModeSelectionView();
    void m_evalModeSelectionInput(int selection);
    void m_setupMode(AppMode mode);
    
    bool m_visible;
    AppState m_state;
    AppMode m_mode;
    ofxPanel m_gui;
    bool m_gui_visible;
    string m_debug_info;
    
public:
    AppUI() {
        ofRegisterKeyEvents(this);
    };
    ~AppUI() {
        ofUnregisterKeyEvents(this);
    };
    
    void setup();
    void update();
    void draw();
    
    void show();
    void hide();
    void clearParameters();
    void addParameters(const ofParameterGroup& group);
    void loadSettings();
    
    // key events
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args){};
    
    // custom events
    ofEvent<AppMode> eventModeSelected;
};