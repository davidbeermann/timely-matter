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
    float m_size_x;
    float m_size_y;
    float m_half_size_x;
    float m_half_size_y;
    unsigned int m_state;
    
public:
    
    Cell(float size_x, float size_y){
        m_size_x = size_x;
        m_size_y = size_y;
        m_half_size_x = size_x * 0.5f;
        m_half_size_y = size_y * 0.5f;
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