#pragma once

#include "ofMain.h"
#include "CellUnit.hpp"
#include "Cell.hpp"
#include "Particle.hpp"


class CellGrid {
    
    float m_segment_width;
    float m_segment_height;
    vector<CellUnit> m_cell_units;
    vector<Cell> m_cells;
    
public:
    
    void setup(unsigned int columns, unsigned int rows);
    void updateMesh(ofMesh& mesh, vector<Particle>& particles, const bool interpolate, const bool infill);
    void draw();
    
};