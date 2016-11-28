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

enum CellGridMode {
    MESH,
    PATH
};

class CellGrid {
    
    float m_segment_width;
    float m_segment_height;
    CellGridMode m_mode;
    vector<CellUnit> m_cell_units;
    vector<Cell> m_cells;
    vector<Cell *> m_contour_cells;
    vector<vector<Cell*>> m_path_cells;
    ofPath m_path;
    ofMesh m_mesh;
    
    void findNeighbor(Cell* cell, vector<Cell*> & list, ofPath & path, NeighborDirection prev_dir = NONE);
    
public:
    
    void setup(unsigned int columns, unsigned int rows);
    void update(vector<Particle> & particles, const bool interpolate, const bool infill);
    void draw();
    
    void setMode(CellGridMode mode) {
        m_mode = mode;
    }
    
    const CellGridMode & getMode() {
        return m_mode;
    }
    
    const bool inPathMode() {
        return m_mode == PATH;
    }
    
    const bool inMeshMode() {
        return m_mode == MESH;
    }
    
    const ofMesh& getMesh() {
        if (inPathMode()) {
            return m_path.getTessellation();
        } else {
            return m_mesh;
        }
    }
    
    ofPath& getPath() {
        return m_path;
    }
    
};