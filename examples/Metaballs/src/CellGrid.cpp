#include "CellGrid.hpp"

#define GRID_DEBUG

typedef vector<CellUnit>::iterator CUIt;
typedef vector<Cell>::iterator CIt;
typedef vector<Particle>::iterator PIt;


void CellGrid::setup(unsigned int columns, unsigned int rows) {
    m_segment_width = (float) ofGetWidth() / (float) columns;
    m_segment_height = (float) ofGetHeight() / (float) rows;
    
    for (float y = 0.f; y < rows + 1; ++y) {
        for (float x = 0.f; x < columns + 1; ++x) {
            m_cell_units.push_back(CellUnit(x * m_segment_width, y * m_segment_height));
        }
    }
    
    for (float y = 0.f; y < rows; ++y) {
        for (float x = 0.f; x < columns; ++x) {
            m_cells.push_back(Cell(m_segment_width, m_segment_height));
            Cell& cell = m_cells[m_cells.size() - 1];
            
            cell.setTopLeftUnit(&m_cell_units[y * (columns + 1) + x]);
            cell.setTopRightUnit(&m_cell_units[y * (columns + 1) + (x + 1)]);
            cell.setBottomRightUnit(&m_cell_units[(y + 1) * (columns + 1) + (x + 1)]);
            cell.setBottomLeftUnit(&m_cell_units[(y + 1) * (columns + 1) + x]);
        }
    }
    
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            unsigned int index = y * columns + x;
            Cell& cell = m_cells[index];
            
            // define edge conditions for cell
            bool topRow = (y == 0);
            bool bottomRow = (y == rows - 1);
            bool leftColumn = (x == 0);
            bool rightColumn = (x == columns - 1);
            cell.setEdgeConditions(topRow, bottomRow, leftColumn, rightColumn);
            
//            ofLog() << "cell index: " << index << " - " << topRow << " " << bottomRow << " " << leftColumn << " " << rightColumn;
            
            // setup neighboring cells
            if (!topRow) {
                cell.setTopNeighbor(&m_cells[(y - 1) * columns + x]);
            }
            if (!bottomRow) {
                cell.setBottomNeighbor(&m_cells[(y + 1) * columns + x]);
            }
            if (!leftColumn) {
                cell.setLeftNeighbor(&m_cells[y * columns + (x - 1)]);
            }
            if (!rightColumn) {
                cell.setRightNeighbor(&m_cells[y * columns + (x + 1)]);
            }
        }
    }
}


void CellGrid::updateMesh(ofMesh& mesh, vector<Particle>& particles, const bool interpolate, const bool infill) {
    // update cell units values based on particles
    for (CUIt cu = m_cell_units.begin(); cu != m_cell_units.end(); ++cu) {
        cu->reset();
        
        for (PIt p = particles.begin(); p != particles.end(); ++p) {
            ofVec3f d = p->getPosition() - cu->getPosition();
//            float diff = p->radius / d.length();
            float diff = p->getRadiusSquared() / d.lengthSquared();
            
            cu->addValue(diff);
        }
    }
    
    // clear all prior vertices in mesh
    mesh.clear();
    
    if (infill) {
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    } else {
        mesh.setMode(OF_PRIMITIVE_LINES);
    }
    
    for (CIt c = m_cells.begin(); c != m_cells.end(); ++c) {
        c->updateState();
        c->calculateMesh(mesh, interpolate, infill);
    }
}


void CellGrid::draw() {
    
#ifdef GRID_DEBUG
    float w, h, w2, h2, r = 2, o = 3;
    for (CIt c = m_cells.begin(); c != m_cells.end(); ++c) {
        w = c->getWidth();
        h = c->getHeight();
        w2 = w * 0.5f;
        h2 = h * 0.5f;
        
        ofPushMatrix();
        ofTranslate(c->getPosition());
        ofPushStyle();
        
        if (c->isInTopRow() || c->isInBottomRow()) {
            ofSetColor(255, 255, 0, 64);
            ofDrawRectangle(0, 0, w, h);
        }
        if (c->isInLeftColumn() || c->isInRightColumn()) {
            ofSetColor(255, 0, 255, 64);
            ofDrawRectangle(0, 0, w, h);
        }
        
        if (c->hasTopNeighbor()) {
            ofSetColor(191, 191, 0, 140);
            ofDrawCircle(w2, o, r);
        }
        if (c->hasBottomNeighbor()) {
            ofSetColor(191, 191, 0, 100);
            ofDrawCircle(w2, h-o, r);
        }
        if (c->hasLeftNeighbor()) {
            ofSetColor(191, 0, 191, 140);
            ofDrawCircle(o, h2, r);
        }
        if (c->hasRightNeighbor()) {
            ofSetColor(191, 0, 191, 100);
            ofDrawCircle(w-o, h2, r);
        }
        
        ofPopStyle();
        ofPopMatrix();
    }
#endif
    
    for (CUIt cu = m_cell_units.begin(); cu != m_cell_units.end(); ++cu) {
        ofPushMatrix();
        ofTranslate(cu->getPosition());
        
        ofPushStyle();
        ofSetCircleResolution(12);
        if (cu->getValue() < 1.f) {
            ofNoFill();
        }
        ofSetColor(255, 0, 0, 255);
        ofDrawCircle(0.f, 0.f, 3.f);
        //        ofDrawBitmapString(to_string(cu->value), 0.f, 12.f);
        ofPopStyle();
        
        ofPopMatrix();
    }
}

