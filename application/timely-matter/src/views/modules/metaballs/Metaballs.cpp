#include "Metaballs.hpp"

using namespace timelymatter;


void Metaballs::setup(const unsigned int & width, const unsigned int & height, const unsigned int & columns, const unsigned int & rows){
    m_cell_grid.setup(width, height, columns, rows);
    m_cell_grid.setMode(MESH);
    
    m_mesh_color.set(255, 255, 255, 255);
    m_clear_color.set(255, 255, 255, 0);
    
    // allocate memory for fbo.
    m_comp_fbo.allocate( width, height, GL_RGBA, 4 );
    
    m_params.setName("Metaballs");
    m_params.add(m_cell_grid.getThresholdParam());
    m_params.add(m_cell_grid.getDampeningParam());
    m_params.add(m_cell_grid.getInterpolateParam());
    m_params.add(m_cell_grid.getInfillParam());
    m_params.add(m_show_cells.set("show cells", false));
    m_params.add(m_show_mesh.set("show mesh", true));
    m_params.add(m_wireframe.set("wireframe", false));
};


void Metaballs::update(vector<Particle> & particles){
    m_cell_grid.update(particles);
    
    // update output fbo
    m_comp_fbo.begin();
    ofClear(m_clear_color);
    
    if (m_show_cells) {
        m_cell_grid.draw();
    }
    
    if (m_show_mesh) {
        if (m_cell_grid.inPathMode() && !m_cell_grid.getInfillParam()) {
            m_cell_grid.getPath().setStrokeColor(m_mesh_color);
            m_cell_grid.getPath().setStrokeWidth(1);
            m_cell_grid.getPath().draw();
        } else {
            ofPushStyle();
            ofSetColor(m_mesh_color);
            if (m_wireframe) {
                m_cell_grid.getMesh().drawWireframe();
            } else {
                m_cell_grid.getMesh().draw();
            }
            ofPopStyle();
        }
    }
    
    m_comp_fbo.end();
};

