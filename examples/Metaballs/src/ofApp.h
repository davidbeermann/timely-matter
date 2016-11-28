#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "CellGrid.hpp"
#include "ParticleSystem.hpp"

// uncomment this macro in order to activate
// single debug particle steered by the mouse.
//#define TEST_PARTICLE_SYSTEM


class ofApp : public ofBaseApp {
    
    CellGrid m_cell_grid;
#ifdef TEST_PARTICLE_SYSTEM
    vector<Particle> m_mouse_particle;
#else
    ParticleSystem m_particle_system;
#endif
    
    ofFloatColor m_hsb_color;
    string info;
    bool m_show_gui;
    
    ofxPanel m_panel;
    ofParameter<float> m_fitting;
    ofParameter<bool> m_move_particles;
    ofParameter<bool> m_show_particles;
    ofParameter<bool> m_show_cells;
    ofParameter<bool> m_show_mesh;
    ofParameter<bool> m_interpolate;
    ofParameter<bool> m_infill;
    ofParameter<bool> m_wireframe;
    
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
//    void keyReleased(int key);
#ifdef TEST_PARTICLE_SYSTEM
    void mouseMoved(int x, int y );
#endif
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
		
};
