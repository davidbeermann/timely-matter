#include "CellGrid.hpp"

#define GRID_DEBUG

typedef vector<CellUnit>::iterator CUIt;
typedef vector<Cell>::iterator CIt;
typedef vector<Particle>::iterator PIt;


void CellGrid::findNeighbor(Cell * cell, vector<Cell *> & list, ofPath & path, NeighborDirection prev_dir) {
    if (cell == nullptr) {
        ofLog() << "findNeighbor() -> NULLPTR";
        return;
    }
//    ofLog() << "ID: " << cell->getId();
    if (list.size() > 0 && cell == list[0]) {
        return;
    }
    list.push_back(cell);
    switch (cell->getState()) {
        // down
        case 1:
        case 9:
        case 13:
            path.lineTo(cell->getVertices()[1]);
            if (cell->hasBottomNeighbor()) {
                return findNeighbor(cell->getBottomNeighbor(), list, path, DOWN);
            } else if (cell->isInBottomRow() && cell->hasLeftNeighbor()) {
                return findNeighbor(cell->getLeftNeighbor(), list, path, LEFT);
            } else {
                ofLog() << "DEAD END - DOWN";
                return;
            }
            break;
        // up
        case 4:
        case 6:
        case 7:
            path.lineTo(cell->getVertices()[1]);
            if (cell->hasTopNeighbor()) {
                return findNeighbor(cell->getTopNeighbor(), list, path, UP);
            } else if (cell->isInTopRow() && cell->hasRightNeighbor()) {
                return findNeighbor(cell->getRightNeighbor(), list, path, RIGHT);
            } else {
                ofLog() << "DEAD END - UP";
                return;
            }
            break;
        // left
        case 8:
        case 12:
        case 14:
            path.lineTo(cell->getVertices()[1]);
            if (cell->hasLeftNeighbor()) {
                return findNeighbor(cell->getLeftNeighbor(), list, path, LEFT);
            } else if (cell->isInLeftColumn() && cell->hasTopNeighbor()) {
                return findNeighbor(cell->getTopNeighbor(), list, path, UP);
            } else {
                ofLog() << "DEAD END - LEFT";
                return;
            }
            break;
        // right
        case 2:
        case 3:
        case 11:
            path.lineTo(cell->getVertices()[1]);
            if (cell->hasRightNeighbor()) {
                return findNeighbor(cell->getRightNeighbor(), list, path, RIGHT);
            } else if (cell->isInRightColumn() && cell->hasBottomNeighbor()) {
                return findNeighbor(cell->getBottomNeighbor(), list, path, DOWN);
            } else {
                ofLog() << "DEAD END - RIGHT";
                return;
            }
            break;
        // saddle
        case 5:
            if (prev_dir == RIGHT && cell->hasTopNeighbor()) {
                path.lineTo(cell->getVertices()[1]);
                return findNeighbor(cell->getTopNeighbor(), list, path, UP);
            } else if (prev_dir == LEFT && cell->hasBottomNeighbor()) {
                path.lineTo(cell->getVertices()[3]);
                return findNeighbor(cell->getBottomNeighbor(), list, path, DOWN);
            } else {
                ofLog() << "DEAD END - 5";
                return;
            }
            break;
        // saddle
        case 10:
            if (prev_dir == UP && cell->hasLeftNeighbor()) {
                path.lineTo(cell->getVertices()[1]);
                return findNeighbor(cell->getLeftNeighbor(), list, path, LEFT);
            } else if (prev_dir == DOWN && cell->hasRightNeighbor()) {
                path.lineTo(cell->getVertices()[3]);
                return findNeighbor(cell->getRightNeighbor(), list, path, RIGHT);
            } else {
                ofLog() << "DEAD END - 10 - prev_dir:" << prev_dir;
                return;
            }
            break;
        // border cells
        case 15:
            switch (prev_dir) {
                    
                case LEFT:
                    if (cell->isInTopRow()) {
                        path.lineTo(cell->getTopLeftUnit()->getPosition());
                    } else if (cell->isInBottomRow()) {
                        path.lineTo(cell->getBottomLeftUnit()->getPosition());
                    } else {
                        ofLog() << "DEAD END - 15 - LEFT";
                    }
                    
                    if (cell->hasLeftNeighbor()) {
                        return findNeighbor(cell->getLeftNeighbor(), list, path, LEFT);
                    } else {
                        return findNeighbor(cell->getTopNeighbor(), list, path, UP);
                    }
                    break;
                    
                case RIGHT:
                    if (cell->isInTopRow()) {
                        path.lineTo(cell->getTopRightUnit()->getPosition());
                    } else if (cell->isInBottomRow()) {
                        path.lineTo(cell->getBottomRightUnit()->getPosition());
                    } else {
                        ofLog() << "DEAD END - 15 - RIGHT";
                    }
                    
                    if (cell->hasRightNeighbor()) {
                        return findNeighbor(cell->getRightNeighbor(), list, path, RIGHT);
                    } else {
                        return findNeighbor(cell->getBottomNeighbor(), list, path, DOWN);
                    }
                    break;
                    
                case UP:
                    if (cell->isInLeftColumn()) {
                        path.lineTo(cell->getTopLeftUnit()->getPosition());
                    } else if (cell->isInRightColumn()) {
                        path.lineTo(cell->getTopRightUnit()->getPosition());
                    } else {
                        ofLog() << "DEAD END - 15 - UP";
                    }
                    
                    if (cell->hasTopNeighbor()) {
                        return findNeighbor(cell->getTopNeighbor(), list, path, UP);
                    } else {
                        return findNeighbor(cell->getRightNeighbor(), list, path, RIGHT);
                    }
                    break;
                    
                case DOWN:
                    if (cell->isInLeftColumn()) {
                        path.lineTo(cell->getBottomLeftUnit()->getPosition());
                    } else if (cell->isInRightColumn()) {
                        path.lineTo(cell->getBottomRightUnit()->getPosition());
                    } else {
                        ofLog() << "DEAD END - 15 - DOWN";
                    }
                    
                    if (cell->hasBottomNeighbor()) {
                        return findNeighbor(cell->getBottomNeighbor(), list, path, DOWN);
                    } else {
                        return findNeighbor(cell->getLeftNeighbor(), list, path, LEFT);
                    }
                    break;
                    
                default:
                    return;
                    break;
            }
            break;
    }
}


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
            unsigned int id = m_cells.size();
            m_cells.push_back(Cell(id, m_segment_width, m_segment_height));
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
    
    m_paths.setMode(ofPath::Mode::POLYLINES);
    m_paths.setColor(ofColor(255, 0, 0, 64));
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
    
    // collect all cells which make the isolines
    vector<Cell *> temp;
    for (CIt c = m_cells.begin(); c != m_cells.end(); ++c) {
        const unsigned int &state = c->updateState();
        // ignore all outer and inner cells, and also saddle points!
        if (state > 0 && state < 15 && state != 5 && state != 10) {
            // store pointer to cell
            temp.push_back(&(*c));
        }
        c->calculateMesh(mesh, interpolate, infill);
    }
    
    // clear list of active cells for update
    m_active_cells.clear();
    
//    ofLog() << "temp cells: " << temp.size();
    
    m_paths.clear();
    
    int count = 0;
    do {
        m_active_cells.push_back(vector<Cell*>());
        vector<Cell*> & current = m_active_cells[m_active_cells.size() - 1];
        
//        m_paths.push_back(ofPath());
//        ofPath& path = m_paths[m_paths.size()-1];
        
        ofPath current_path;
        
        Cell* first_cell = temp[0];
        
        current_path.moveTo(first_cell->getVertices()[0]);
        
        // find all neighbors starting from first cell stored in temp vector.
        // store found cells in active cells vector.
        findNeighbor(first_cell, current, current_path);
        
        current_path.close();
        m_paths.append(current_path);
        
        vector<Cell *>::iterator t, a;
        for (t = temp.begin(); t != temp.end();) {
            bool match = false;
            for (a = current.begin(); a != current.end(); ++a) {
                if (*t == *a) {
                    // when erasing position of t, t points automatically to the next position in the vector.
                    temp.erase(t);
                    match = true;
                    break;
                }
            }
            // only iterate if no match was found.
            if(!match){
                t++;
            }
        }
        
//        ofLog() << count++ << " - " << "current cells: " << current.size() << " - temp cells: " << temp.size();
        
    } while (temp.size() > 0);
    
//    ofLog() << "temp cells: " << temp.size();
//    ofLog() << "active cells: " << m_active_cells.size();
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
    if (m_active_cells.size() > 0) {
        Cell *c;
        for (int i = 0; i < m_active_cells.size(); ++i) {
            for (int j = 0; j < m_active_cells[i].size(); ++j) {
                c = m_active_cells[i][j];
                ofPushMatrix();
                ofTranslate(c->getPosition());
                ofPushStyle();
                ofSetColor(191, 0, 0, 128);
                ofDrawRectangle(0, 0, c->getWidth(), c->getHeight());
                ofPopStyle();
                ofPopMatrix();
            }
        }
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

