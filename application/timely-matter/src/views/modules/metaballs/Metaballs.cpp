#include "Metaballs.hpp"

using namespace timelymatter;


void Metaballs::setup(const unsigned int & width, const unsigned int & height, const unsigned int & columns, const unsigned int & rows){
    m_cell_grid.setup(width, height, columns, rows);
    m_cell_grid.setMode(MESH);
    
    m_hsb_color.set(ofRandom(1.f), ofRandom(0.2f, 0.8f), 0.9f, 0.75f);
    
    m_params.setName("Metaballs");
    m_params.add(m_fitting.set("contour fitting", 0.75f, 0.5f, 1.f));
    m_params.add(m_show_cells.set("show cells", false));
    m_params.add(m_show_mesh.set("show mesh", true));
    m_params.add(m_interpolate.set("interpolate", false));
    m_params.add(m_infill.set("infill", false));
    m_params.add(m_wireframe.set("wireframe", false));
};


void Metaballs::update(vector<Particle> & particles){
    m_cell_grid.update(particles, m_interpolate, m_infill, m_fitting);
    
    float h = m_hsb_color.getHue() + ofRandom(-0.01f, 0.01f);
    if (h < 0.f) h = 1 + h;
    if (h > 1.f) h = h - 1;
    m_hsb_color.setHue(h);
    float b = m_hsb_color.getBrightness() + ofRandom(-0.01f, 0.01f);
    if (b < 0.2f) b = 0.2f;
    if (b > 0.8f) b = 0.8f;
    m_hsb_color.setBrightness(b);
};


void Metaballs::draw(){
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
};

