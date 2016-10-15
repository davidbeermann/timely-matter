#pragma once

#include "ofMain.h"
#include "CellUnit.hpp"


class Cell {
    
    void calculateStraightLines(vector<ofVec3f>& vertices);
    void calculateInterpolatedLines(vector<ofVec3f>& vertices);
    void transformLinesToInfill(vector<ofVec3f>& vertices);
    
    CellUnit* m_tlu = nullptr; // top left cell unit
    CellUnit* m_tru = nullptr; // top right cell unit
    CellUnit* m_bru = nullptr; // bottom right cell unit
    CellUnit* m_blu = nullptr; // bottom left cell unit
    float m_size;
    float m_half_size;
    unsigned int m_state;
    
public:
    
    Cell(float cell_size){
        m_size = cell_size;
        m_half_size = cell_size * 0.5f;
        m_state = 0;
    }
    
    void setTopLeftUnit(CellUnit* unit) {
        m_tlu = unit;
    }
    
    void setTopRightUnit(CellUnit* unit) {
        m_tru = unit;
    }
    
    void setBottomRightUnit(CellUnit* unit) {
        m_bru = unit;
    }
    
    void setBottomLeftUnit(CellUnit* unit) {
        m_blu = unit;
    }
    
    void updateState();
    void calculateMesh(ofMesh& mesh, bool interpolated = false, bool infill = false);
    
};