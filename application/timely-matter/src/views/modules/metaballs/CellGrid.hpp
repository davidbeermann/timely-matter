#pragma once

#include "ofMain.h"
#include "CellUnit.hpp"
#include "Cell.hpp"
#include "Particle.hpp"


namespace timelymatter {

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
        
        ofParameter<float> m_threshold_param;
        ofParameter<float> m_dampening_param;
        
        bool m_interpolate;
        bool m_infill;
        
        void findNeighbor(Cell* cell, vector<Cell*> & list, ofPath & path, NeighborDirection prev_dir = NONE);
        
    public:
        
        void setup(const unsigned int & width, const unsigned int & height, const unsigned int & columns, const unsigned int & rows);
        void update(vector<Particle> & particles);
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
        
        ofParameter<float> & getThresholdParam() {
            return m_threshold_param;
        }
        ofParameter<float> & getDampeningParam() {
            return m_dampening_param;
        }
        
        const bool & getInterpolate() {
            return m_interpolate;
        }
        const bool & getInfill() {
            return m_infill;
        }
        void setInterpolate(const bool value) {
            m_interpolate = value;
        }
        void setInfill(const bool value) {
            m_infill = value;
        }
    };

}