#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "CellGrid.hpp"
#include "ParticleSystem.hpp"


class ofApp : public ofBaseApp {
    
    CellGrid m_cell_grid;
    ParticleSystem m_particle_system;
    ofMesh m_mesh;
    
    string info;
    bool m_show_gui;
    
    ofxPanel m_panel;
    ofParameter<float> m_fitting;
    ofParameter<bool> m_show_particles;
    ofParameter<bool> m_move_particles;
    ofParameter<bool> m_show_cells;
    ofParameter<bool> m_show_mesh;
    ofParameter<bool> m_interpolate;
    ofParameter<bool> m_infill;
    
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
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
