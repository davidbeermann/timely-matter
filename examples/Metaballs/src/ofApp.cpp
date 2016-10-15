#include "ofApp.h"

#define PARTICLE_COUNT 15
#define X_SEGMENTS 60
#define Y_SEGMENTS 60
#define SEGMENT_SIZE 10


void ofApp::setup(){
    ofSetWindowTitle("2D Metaballs");
    ofSetBackgroundColor(0);
    
    m_cell_grid.setup(X_SEGMENTS, Y_SEGMENTS);
    
    m_particle_system.setup(PARTICLE_COUNT);
    
    m_show_gui = false;
    
    m_panel.setup();
    m_panel.setName("Metaballs");
    m_panel.add(m_fitting.set("fitting", 1.f, 0.2f, 1.f));
    m_panel.add(m_show_particles.set("show particles", false));
    m_panel.add(m_move_particles.set("move particles", true));
    m_panel.add(m_show_cells.set("show cells", false));
    m_panel.add(m_show_mesh.set("show mesh", true));
    m_panel.add(m_interpolate.set("interpolate", false));
    m_panel.add(m_infill.set("infill", false));
}


void ofApp::update(){
    if (m_move_particles) {
        m_particle_system.update();
    }
    
    if (m_show_mesh) {
        m_cell_grid.updateMesh(m_mesh, m_particle_system.getParticles(), m_interpolate, m_infill);
    }
    
    info = "";
    info += "FPS: " + to_string((int) ofGetFrameRate());
    info += "\nNUM VERTICES: " + to_string((int) m_mesh.getNumVertices());
    if (m_infill) {
        info += "\nNUM TRIANGLES: " + to_string((int) (m_mesh.getNumVertices()/3));
    } else {
        info += "\nNUM LINES: " + to_string((int) (m_mesh.getNumVertices()/2));
    }
}


void ofApp::draw(){
    if (m_show_particles) {
        m_particle_system.draw();
    }
    
    if (m_show_cells) {
        m_cell_grid.draw();
    }
    
    if (m_show_mesh) {
        m_mesh.draw();
    }
    
    ofPushStyle();
    ofSetColor(255, 0, 127, 255);
    ofDrawBitmapString(info, 10, 21);
    ofPopStyle();
    
    if (m_show_gui) {
        m_panel.draw();
    }
}


void ofApp::keyPressed(int key){
    if (key == 'g') {
        m_show_gui = !m_show_gui;
    }
}


