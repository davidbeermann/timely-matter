#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "MeterGrid.h"
#include "DebugView.h"
#include "PerlinNoiseFbo.hpp"


class ofApp : public ofBaseApp {
    
    const int GRID_RESOLUTION = 32;
    const float SAMPLING_THRESHOLD = 255.f / 4.f;
    
    bool m_show_gui = false;
    vector<int> m_edge_unit_indices;
    
    ofVec2f m_content_origin;
    ofxPanel m_gui;
    PerlinNoiseFbo m_noise;
    MeterGrid m_grid;
    DebugView m_debug_view;
    
    void setupGui();
    void setContentOrigin(int w, int h);
    
public:
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
    void windowResized(int w, int h);

};
