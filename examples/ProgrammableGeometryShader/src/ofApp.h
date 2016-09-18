#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
    
    ofEasyCam m_cam;
    ofVboMesh m_mesh;
    ofShader m_shader;
    ofFbo m_fbo;
    ofxPanel m_panel;
    
    ofParameter<bool> m_param_enable_shader;
    ofParameter<int> m_param_segments;
    ofParameter<int> m_param_radius;
    ofParameter<int> m_param_amplitude;
    ofParameter<float> m_param_speed;
    ofParameter<bool> m_param_clear_fbo;
    
    string m_info;
    bool m_show_panel;
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
};
