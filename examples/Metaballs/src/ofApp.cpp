#include "ofApp.h"

#define PARTICLE_COUNT 25 // 15 25
#define COLUMNS 128 // 32 128
#define ROWS 64 // 32 64


void ofApp::setup(){
    ofSetWindowTitle("2D Metaballs");
    ofSetBackgroundColor(0);
    
    m_cell_grid.setup(COLUMNS, ROWS);
    m_cell_grid.setMode(PATH);
    
#ifdef TEST_PARTICLE_SYSTEM
    m_mouse_particle.push_back(Particle(ofGetWidth()*0.5f, ofGetHeight()*0.5f, 75));
#else
    m_particle_system.setup(PARTICLE_COUNT);
#endif
    
    m_hsb_color.set(ofRandom(1.f), ofRandom(0.2f, 0.8f), 0.9f, 0.75f);
    
    m_show_gui = false;
    
    m_panel.setup();
    m_panel.setName("Metaballs");
    m_panel.add(m_fitting.set("contour fitting", 0.75f, 0.5f, 1.f));
    m_panel.add(m_move_particles.set("move particles", true));
    m_panel.add(m_show_particles.set("show particles", false));
    m_panel.add(m_show_cells.set("show cells", false));
    m_panel.add(m_show_mesh.set("show mesh", true));
    m_panel.add(m_interpolate.set("interpolate", false));
    m_panel.add(m_infill.set("infill", false));
    m_panel.add(m_wireframe.set("wireframe", false));
}


void ofApp::update() {
#ifdef TEST_PARTICLE_SYSTEM
    m_cell_grid.update(m_mouse_particle, m_interpolate, m_infill, m_fitting);
#else
    if (m_move_particles) {
        m_particle_system.update();
    }
    
    m_cell_grid.update(m_particle_system.getParticles(), m_interpolate, m_infill, m_fitting);
#endif
    
    float h = m_hsb_color.getHue() + ofRandom(-0.01f, 0.01f);
    if (h < 0.f) h = 1 + h;
    if (h > 1.f) h = h - 1;
    m_hsb_color.setHue(h);
    float b = m_hsb_color.getBrightness() + ofRandom(-0.01f, 0.01f);
    if (b < 0.2f) b = 0.2f;
    if (b > 0.8f) b = 0.8f;
    m_hsb_color.setBrightness(b);
    
    info = "FPS: " + to_string((int) ofGetFrameRate());
    info += " - MODE: ";
    info += m_cell_grid.inPathMode() ? "PATH" : "MESH";
    if (m_show_mesh) {
        info += "\nNUM VERTICES: " + to_string((int) m_cell_grid.getMesh().getNumVertices());
        if (m_infill) {
            info += "\nNUM TRIANGLES: " + to_string((int) (m_cell_grid.getMesh().getNumVertices()/3));
        } else {
            if (m_cell_grid.inMeshMode()) {
                info += "\nNUM LINES: " + to_string((int) (m_cell_grid.getMesh().getNumVertices()/2));
            }
        }
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
        if (m_cell_grid.inPathMode() && !m_infill) {
            m_cell_grid.getPath().setStrokeColor(m_hsb_color);
            m_cell_grid.getPath().setStrokeWidth(1);
            m_cell_grid.getPath().draw();
        } else {
            ofPushStyle();
            ofSetColor(m_hsb_color);
            if (m_wireframe) {
                m_cell_grid.getMesh().drawWireframe();
            } else {
                m_cell_grid.getMesh().draw();
            }
            ofPopStyle();
        }
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
        case 'w':
            m_wireframe = !m_wireframe;
            break;
        case OF_KEY_TAB:
            if (m_cell_grid.inPathMode()) {
                m_cell_grid.setMode(MESH);
            } else {
                m_cell_grid.setMode(PATH);
            }
            break;
        default:
            break;
    }
}


#ifdef TEST_PARTICLE_SYSTEM
void ofApp::mouseMoved(int x, int y ) {
    if (m_move_particles) {
        if (x < m_mouse_particle[0].getRadius()) x = m_mouse_particle[0].getRadius();
        else if (x > ofGetWidth() - m_mouse_particle[0].getRadius()) x = ofGetWidth() - m_mouse_particle[0].getRadius();
        
        if (y < m_mouse_particle[0].getRadius()) y = m_mouse_particle[0].getRadius();
        else if (y > ofGetHeight() - m_mouse_particle[0].getRadius()) y = ofGetHeight() - m_mouse_particle[0].getRadius();
        
        m_mouse_particle[0].setPosition(ofVec3f(x,y,0.f));
    }
}
#endif


