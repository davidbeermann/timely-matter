#pragma once

#include "ofMain.h"
#include "CellUnit.hpp"
#include "Cell.hpp"
#include "Particle.hpp"


enum NeighborDirection {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class CellGrid {
    
    float m_segment_width;
    float m_segment_height;
    vector<CellUnit> m_cell_units;
    vector<Cell> m_cells;
    vector<vector<Cell*>> m_active_cells;
    ofPath m_paths;
    
    void findNeighbor(Cell* cell, vector<Cell*> & list, ofPath & path, NeighborDirection prev_dir = NONE);
    
public:
    
    void setup(unsigned int columns, unsigned int rows);
    void updateMesh(ofMesh& mesh, vector<Particle>& particles, const bool interpolate, const bool infill);
    void draw();
    
    const ofPath& getPaths() {
        return m_paths;
    }
    
};