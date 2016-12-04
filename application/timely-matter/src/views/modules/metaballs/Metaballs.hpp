#pragma once

#include "ofMain.h"
#include "CellGrid.hpp"
#include "Particle.hpp"


namespace timelymatter {

    class Metaballs {

        CellGrid m_cell_grid;
        ofFloatColor m_hsb_color;
        
        ofParameterGroup m_params;
        ofParameter<float> m_fitting;
        ofParameter<bool> m_show_cells;
        ofParameter<bool> m_show_mesh;
        ofParameter<bool> m_interpolate;
        ofParameter<bool> m_infill;
        ofParameter<bool> m_wireframe;
        
    public:
        void setup(const unsigned int & width, const unsigned int & height, const unsigned int & columns, const unsigned int & rows);
        void update(vector<Particle> & particles);
        void draw();
        
        ofParameterGroup & getParams() { return m_params; }

    };

}