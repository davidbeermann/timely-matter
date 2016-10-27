#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "PostFxQueue.hpp"
#include "GeneratedMeshFxModule.hpp"
#include "GaussianBlurFxModule.hpp"


class ofApp : public ofBaseApp{
    
    PostFxQueue m_post_fx_queue;
    GeneratedMeshFxModule m_mesh_module;
    GaussianBlurFxModule m_blur_module;
    ofxPanel m_gui;
    
public:
    void setup();
    void update();
    void draw();
//    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
		
};
