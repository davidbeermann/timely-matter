#include "ofApp.h"
#include "MarchingSquares.h"

#define CONTENT_WIDTH 1024
#define CONTENT_HEIGHT 768


void ofApp::setup() {
    // setup fbo to generate perlin noise image/pixel data
    m_noise.setup( CONTENT_WIDTH, CONTENT_HEIGHT );
    
    // setup meter grid with fixed resolution and sampling threshold
    m_grid.setup( CONTENT_WIDTH / GRID_RESOLUTION, CONTENT_HEIGHT / GRID_RESOLUTION, GRID_RESOLUTION, SAMPLING_THRESHOLD );
    
    setupGui();

    // setup initial content origin
    setContentOrigin( ofGetWidth(), ofGetHeight() );
}


void ofApp::update() {
    // write current fps to window title
    ofSetWindowTitle("Marching Squares Example - FPS:" + to_string((int)ofGetFrameRate()));
    
    // update grid with data from perlin noise
    m_noise.update();
    m_grid.update( m_noise.getImage() );
    
    // calculate marching squares and update grid
    m_edge_unit_indices.clear();
    MarchingSquares::updateUnits( m_grid.getGridUnits(), m_edge_unit_indices );
//    m_grid.updateInnerNeighborCounts( m_edge_unit_indices );
}


void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(m_content_origin);

    m_noise.draw();
    m_debug_view.draw( m_grid.getSamplePoints(), m_grid.getGridUnits() );

    ofPopMatrix();

    if (m_show_gui) {
        m_gui.draw();
    }
}


void ofApp::keyReleased(int key) {
    switch (key) {
        case 'g':
            m_show_gui = !m_show_gui;
            break;
        default:
            break;
    }
}


void ofApp::windowResized(int w, int h) {
    setContentOrigin(w, h);
}


void ofApp::setupGui() {
    // set title and size of gui panel
    m_gui.setup("Marching Squares");
    m_gui.setSize(300, 500);
    m_gui.setDefaultWidth(300);
    
    // add parameter groups
    m_gui.add( m_noise.getParams() );
    m_gui.add( m_debug_view.getGuiParameters() );
}


// method to calculate top left coordinate centered in window
void ofApp::setContentOrigin(int w, int h) {
    m_content_origin.x = (int) ((w - CONTENT_WIDTH) * 0.5f);
    m_content_origin.y = (int) ((h - CONTENT_HEIGHT) * 0.5f);
}










