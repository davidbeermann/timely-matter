#include "ofApp.h"

#define PARTICLE_COUNT 15 //25
#define COLUMNS 32 //128
#define ROWS 32 //64


void ofApp::setup(){
    ofSetWindowTitle("2D Metaballs");
    ofSetBackgroundColor(0);
    
    m_cell_grid.setup(COLUMNS, ROWS);
    
#ifdef TEST_PARTICLE_SYSTEM
    m_mouse_particle.push_back(Particle(ofGetWidth()*0.5f, ofGetHeight()*0.5f, 75));
#else
    m_particle_system.setup(PARTICLE_COUNT);
#endif
    
    m_show_gui = false;
    
    m_panel.setup();
    m_panel.setName("Metaballs");
    m_panel.add(m_show_particles.set("show particles", false));
    m_panel.add(m_move_particles.set("move particles", true));
    m_panel.add(m_show_cells.set("show cells", false));
    m_panel.add(m_show_mesh.set("show mesh", true));
    m_panel.add(m_interpolate.set("interpolate", false));
    m_panel.add(m_infill.set("infill", false));
}


void ofApp::update() {
#ifdef TEST_PARTICLE_SYSTEM
    if (m_show_mesh) {
        m_cell_grid.updateMesh(m_mesh, m_mouse_particle, m_interpolate, m_infill);
    }
#else
    if (m_move_particles) {
        m_particle_system.update();
    }
    
    if (m_show_mesh) {
        m_cell_grid.updateMesh(m_mesh, m_particle_system.getParticles(), m_interpolate, m_infill);
    }
#endif
    
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
    #ifdef TEST_PARTICLE_SYSTEM
        ofPushMatrix();
        ofTranslate(m_mouse_particle[0].getPosition());
        
        ofPushStyle();
        ofSetCircleResolution(64);
        ofSetColor(255, 255, 255, 127);
        ofDrawCircle(0.f, 0.f, m_mouse_particle[0].getRadius());
        ofPopStyle();
        
        ofPopMatrix();
    #else
        m_particle_system.draw();
    #endif
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
    switch (key) {
        case 'g':
            m_show_gui = !m_show_gui;
            break;
        case ' ':
            m_move_particles = !m_move_particles;
            break;
        case 'p':
            m_show_particles = !m_show_particles;
            break;
        case 'c':
            m_show_cells = !m_show_cells;
            break;
        case 'm':
            m_show_mesh = !m_show_mesh;
            break;
        case 'i':
            m_interpolate = !m_interpolate;
            break;
        case 'f':
            m_infill = !m_infill;
            break;
        default:
            break;
    }
}


#ifdef TEST_PARTICLE_SYSTEM
void ofApp::mouseMoved(int x, int y ) {
    if (m_move_particles) {
        m_mouse_particle[0].setPosition(ofVec3f(x,y,0.f));
    }
}
#endif


