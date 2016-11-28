#pragma once

#include "ofMain.h"
#include "CellUnit.hpp"


class Cell {
    
    void calculateStraightLines();
    void calculateInterpolatedLines();
    void transformLinesToNaiveInfill();
    
    CellUnit* m_tlu = nullptr; // top left cell unit
    CellUnit* m_tru = nullptr; // top right cell unit
    CellUnit* m_bru = nullptr; // bottom right cell unit
    CellUnit* m_blu = nullptr; // bottom left cell unit
    Cell* m_nt = nullptr; // neighbor to the top
    Cell* m_nb = nullptr; // neighbor to the bottom
    Cell* m_nl = nullptr; // neighbor to the left
    Cell* m_nr = nullptr; // neighbor to the right
    unsigned int m_id;
    float m_size_x;
    float m_size_y;
    float m_half_size_x;
    float m_half_size_y;
    unsigned int m_state;
    bool m_in_top_row;
    bool m_in_bottom_row;
    bool m_in_left_column;
    bool m_in_right_column;
    vector<ofVec3f> m_vertices;
    
public:
    
    Cell(unsigned int id, float size_x, float size_y){
        m_id = id;
        m_size_x = size_x;
        m_size_y = size_y;
        m_half_size_x = size_x * 0.5f;
        m_half_size_y = size_y * 0.5f;
        m_state = 0;
        m_in_top_row = false;
        m_in_bottom_row = false;
        m_in_left_column = false;
        m_in_right_column = false;
    }
    
    const unsigned int& getId() {
        return m_id;
    }
    
    const vector<ofVec3f>& getVertices() {
        return m_vertices;
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
    
    CellUnit* getTopLeftUnit() {
        return m_tlu;
    }
    
    CellUnit* getTopRightUnit() {
        return m_tru;
    }
    
    CellUnit* getBottomRightUnit() {
        return m_bru;
    }
    
    CellUnit* getBottomLeftUnit() {
        return m_blu;
    }
    
    void setTopNeighbor(Cell* cell) {
        m_nt = cell;
    }
    
    void setBottomNeighbor(Cell* cell) {
        m_nb = cell;
    }
    
    void setLeftNeighbor(Cell* cell) {
        m_nl = cell;
    }
    
    void setRightNeighbor(Cell* cell) {
        m_nr = cell;
    }
    
    Cell* getTopNeighbor() {
        return m_nt;
    }
    
    Cell* getBottomNeighbor() {
        return m_nb;
    }
    
    Cell* getLeftNeighbor() {
        return m_nl;
    }
    
    Cell* getRightNeighbor() {
        return m_nr;
    }
    
    bool hasTopNeighbor() {
        return m_nt != nullptr;
    }
    
    bool hasBottomNeighbor() {
        return m_nb != nullptr;
    }
    
    bool hasLeftNeighbor() {
        return m_nl != nullptr;
    }
    
    bool hasRightNeighbor() {
        return m_nr != nullptr;
    }
    
    void setEdgeConditions(bool isTopRow, bool isBottomRow, bool isLeftColumn, bool isRightColumn) {
        m_in_top_row = isTopRow;
        m_in_bottom_row = isBottomRow;
        m_in_left_column = isLeftColumn;
        m_in_right_column = isRightColumn;
    }
    
    const bool& isInTopRow() {
        return m_in_top_row;
    }
    
    const bool& isInBottomRow() {
        return m_in_bottom_row;
    }
    
    const bool& isInLeftColumn() {
        return m_in_left_column;
    }
    
    const bool& isInRightColumn() {
        return m_in_right_column;
    }
    
    const ofVec3f& getPosition() {
        if (m_tlu != nullptr) {
            return m_tlu->getPosition();
        } else {
            ofLog() << "getPosition()";
            ofVec3f v;
            return v;
        }
    }
    
    const float getWidth() {
        if (m_tru != nullptr && m_tlu != nullptr) {
            return m_tru->getPosition().x - m_tlu->getPosition().x;
        } else {
            ofLog() << "getWidth()";
            return 0.f;
        }
    }
    
    const float getHeight() {
        if (m_blu != nullptr && m_tlu != nullptr) {
            return m_blu->getPosition().y - m_tlu->getPosition().y;
        } else {
            ofLog() << "getHeight()";
            return 0.f;
        }
    }
    
    const unsigned int& getState() {
        return m_state;
    }
    
    void addNaiveInfillVertices() {
        transformLinesToNaiveInfill();
    }
    
    void update(bool interpolated = false);
    
};