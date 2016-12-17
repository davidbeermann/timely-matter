#pragma once

#include "ofMain.h"
#include "CellGrid.hpp"
#include "Particle.hpp"


namespace timelymatter {

    class Metaballs {

        CellGrid m_cell_grid;
        ofColor m_mesh_color;
        ofColor m_clear_color;
        ofFbo m_mesh_fbo;
        ofFbo m_wireframe_fbo;
        
        ofParameterGroup m_params;
//        ofParameter<bool> m_show_cells;
        
    public:
        void setup(const unsigned int & width, const unsigned int & height, const unsigned int & columns, const unsigned int & rows);
        void update(vector<Particle> & particles);
        
        ofFbo & getMeshFbo() { return m_mesh_fbo; }
        ofFbo & getWireframeFbo() { return m_wireframe_fbo; }
        ofParameterGroup & getParams() { return m_params; }
        
        void setInterpolation(const bool value) {
            m_cell_grid.setInterpolate(value);
        }
        void setInfill(const bool value) {
            m_cell_grid.setInfill(value);
        }

    };

}