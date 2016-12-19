#pragma once

#include "ofMain.h"
#include "CellUnit.hpp"
#include "Cell.hpp"
#include "Particle.hpp"
#include "RenderParams.hpp"


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
        
        float m_threshold;
        float m_dampening;
        bool m_interpolate;
        bool m_infill;
        
        void findNeighbor(Cell* cell, vector<Cell*> & list, ofPath & path, NeighborDirection prev_dir = NONE);
        
    public:
        
        static float const THRESHOLD_MIN;
        static float const THRESHOLD_MAX;
        static float const DAMPENING_MIN;
        static float const DAMPENING_MAX;
        
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
        
        float const & getThreshold() {
            return m_threshold;
        }
        float const & getDampening() {
            return m_dampening;
        }
        const bool & getInterpolate() {
            return m_interpolate;
        }
        const bool & getInfill() {
            return m_infill;
        }
        
        void setThreshold(float const value) {
            if (value > THRESHOLD_MAX) m_threshold = THRESHOLD_MAX;
            else if (value < THRESHOLD_MIN) m_threshold = THRESHOLD_MIN;
            else m_threshold = value;
        }
        void setDampening(float const value) {
            if (value > DAMPENING_MAX) m_dampening = DAMPENING_MAX;
            else if (value < DAMPENING_MIN) m_dampening = DAMPENING_MIN;
            else m_dampening = value;
        }
        void setInterpolate(bool const value) {
            m_interpolate = value;
        }
        void setInfill(bool const value) {
            m_infill = value;
        }
    };

}