#pragma once

#include "ofMain.h"
#include "CellGrid.hpp"
#include "Particle.hpp"


namespace timelymatter {

    class Metaballs {

        CellGrid m_cell_grid;
        ofColor m_mesh_color;
        ofColor m_clear_color;
        ofFbo m_output_fbo;
        ofFbo m_wireframe_fbo;
        
        ofParameterGroup m_params;
        ofParameter<bool> m_show_cells;
        ofParameter<bool> m_show_mesh;
        ofParameter<bool> m_wireframe;
        
    public:
        void setup(const unsigned int & width, const unsigned int & height, const unsigned int & columns, const unsigned int & rows);
        void update(vector<Particle> & particles);
        
        ofFbo & getOutputFbo() { return m_output_fbo; }
        ofFbo & getWireframeFbo() { return m_wireframe_fbo; }
        ofParameterGroup & getParams() { return m_params; }

    };

}