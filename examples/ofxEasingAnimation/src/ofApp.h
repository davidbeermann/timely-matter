#pragma once

#include "ofMain.h"
#include "ofxEasing.h"


class ofApp : public ofBaseApp {
    
    void reset();
    
    ofxeasing::function func_w, func_h, func_r;
    ofRectangle m_rect;
    ofColor m_color;
    float m_duration, m_delay;
    float m_start, m_end;
    float m_progress;
    bool m_animating, m_running;

public:
    void setup();
    void update();
    void draw();
//    void keyPressed(int key);
//    void keyReleased(int key);
    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
		
};
