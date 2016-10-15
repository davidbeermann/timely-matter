#include "CellGrid.hpp"

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
}


void CellGrid::updateMesh(ofMesh& mesh, vector<Particle>& particles, const bool interpolate, const bool infill) {
    for (CUIt cu = m_cell_units.begin(); cu != m_cell_units.end(); ++cu) {
        cu->reset();
        
        for (PIt p = particles.begin(); p != particles.end(); ++p) {
            ofVec3f d = p->getPosition() - cu->getPosition();
//            float diff = p->radius / d.length();
            float diff = p->getRadiusSquared() / d.lengthSquared();
            
            cu->addValue(diff);
        }
    }
    
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

