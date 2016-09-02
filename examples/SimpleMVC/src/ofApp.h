#pragma once

#include "ofMain.h"
#include "AppEvents.hpp"
#include "ViewManager.hpp"
#include "ChangeStateCommand.hpp"


class ofApp : public ofBaseApp {
    AppEvents& m_events;
    ViewManager m_view_manager;
    ChangeStateCommand m_change_state_cmd;
public:
    ofApp() : m_events(AppEvents::get()) {};
    
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
};
