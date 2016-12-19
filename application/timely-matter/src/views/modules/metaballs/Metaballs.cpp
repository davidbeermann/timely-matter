#include "Metaballs.hpp"

using namespace timelymatter;


void Metaballs::setup(const unsigned int & width, const unsigned int & height, const unsigned int & columns, const unsigned int & rows) {
    
    m_cell_grid.setup(width, height, columns, rows);
    m_cell_grid.setMode(MESH);
    
    m_mesh_color.set(255, 255, 255, 255);
    m_clear_color.set(255, 255, 255, 0);
    
    // allocate memory for fbo.
    m_mesh_fbo.allocate( width, height, GL_RGBA, 4 );
    m_wireframe_fbo.allocate( width, height, GL_RGBA, 4 );
    
}


void Metaballs::update(vector<Particle> & particles) {
    
    m_cell_grid.update(particles);
    
    // update output fbo
    m_mesh_fbo.begin();
    ofClear(m_clear_color);
    
    //TODO create separate fbo for cells
//    if (m_show_cells) {
//        m_cell_grid.draw();
//    }
    
    if (m_cell_grid.inPathMode() && !m_cell_grid.getInfill()) {
        m_cell_grid.getPath().setStrokeColor(m_mesh_color);
        m_cell_grid.getPath().setStrokeWidth(1);
        m_cell_grid.getPath().draw();
    } else {
        ofPushStyle();
        ofSetColor(m_mesh_color);
        m_cell_grid.getMesh().draw();
        ofPopStyle();
    }
    
    m_mesh_fbo.end();
    
    // update wireframe fbo
    m_wireframe_fbo.begin();
    ofClear(m_clear_color);
    
    ofPushStyle();
    ofSetColor(m_mesh_color);
    m_cell_grid.getMesh().drawWireframe();
    ofPopStyle();
    
    m_wireframe_fbo.end();
}

