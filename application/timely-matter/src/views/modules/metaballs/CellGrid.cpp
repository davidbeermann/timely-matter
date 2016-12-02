#include "CellGrid.hpp"

// this macro enables additional visual information on the grid
//#define GRID_DEBUG

using namespace timelymatter;

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


void CellGrid::setup(const unsigned int & width, const unsigned int & height, const unsigned int & columns, const unsigned int & rows) {
    m_segment_width = (float) width / (float) columns;
    m_segment_height = (float) height / (float) rows;
    m_mode = MESH;
    
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
    
    m_path.setMode(ofPath::Mode::POLYLINES);
    m_path.setColor(ofColor(255, 0, 0, 64));
}


void CellGrid::update(vector<Particle> & particles, const bool interpolate, const bool infill, const float fitting) {
    // update cell units values based on distances to particles
    for (CUIt cu = m_cell_units.begin(); cu != m_cell_units.end(); ++cu) {
        cu->reset();
        
        for (PIt p = particles.begin(); p != particles.end(); ++p) {
            ofVec3f d = p->getPosition() - cu->getPosition();
            // this calculation involves a square root operation:
            // length => sqrt( a*a + b*b );
//            float diff = p->radius / d.length();
            // take the squared radius in order to avoid square root calculation!
            float diff = (p->getRadiusSquared() / d.lengthSquared()) * fitting;
            
            cu->addValue(diff);
        }
    }
    
    if (inMeshMode()) {
        // remove all prior vertices from mesh
        m_mesh.clear();
        
        // set correct mode for mesh
        if (infill) {
            m_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        } else {
            m_mesh.setMode(OF_PRIMITIVE_LINES);
        }
    }
    
    if (inPathMode()) {
        // this vector collects all cells which are part of the contours.
        // except for ambiguous cases which are not useful to find closed contours.
        m_contour_cells.clear();
    }
        
    for (CIt c = m_cells.begin(); c != m_cells.end(); ++c) {
        // update cell after each cell unit was updated
        c->update(interpolate);
        
        if (inPathMode()) {
            // get marching square state of cell
            const unsigned int &state = c->getState();
            
            // ignore all outer and inner cells, and also saddle points!
            if (state > 0 && state < 15 && state != 5 && state != 10) {
                // store pointer to cell
                m_contour_cells.push_back(&(*c));
            }
        }
        
        if (inMeshMode()) {
            if (infill) {
                c->addNaiveInfillVertices();
            }
            
            // transfer cell vertices to mesh
            m_mesh.addVertices(c->getVertices());
        }
    }
    
    if (inPathMode()) {
        // clear all previous paths
        m_path.clear();
        
        m_path.setFilled(infill);
        if (!infill) {
            m_path.setStrokeWidth(1);
        }
        
        // clear all previous path cells
        m_path_cells.clear();
        
        // loop over contour cells to find all connected cells for each path
        do {
            // create new vector to store path cells
            m_path_cells.push_back(vector<Cell*>());
            vector<Cell*> & current = m_path_cells[m_path_cells.size() - 1];

            // create new temporary path
            ofPath current_path;
            
            // select first contoru cell as starting point for recursive function
            Cell* first_cell = m_contour_cells[0];
            
            // set sarting point of current path
            current_path.moveTo(first_cell->getVertices()[0]);
            
            // find all neighbors starting from first cell.
            // all cells defining a single path will be stored in vector.
            findNeighbor(first_cell, current, current_path);
            
            // close path and append it to main path object
            current_path.close();
            m_path.append(current_path);
            
            // remove all cells found in current path from contour cell vector
            vector<Cell *>::iterator t, a;
            for (t = m_contour_cells.begin(); t != m_contour_cells.end();) {
                bool match = false;
                for (a = current.begin(); a != current.end(); ++a) {
                    if (*t == *a) {
                        // when erasing position of t, t points automatically to the next position in the vector.
                        m_contour_cells.erase(t);
                        match = true;
                        break;
                    }
                }
                // only iterate if no match was found!!!
                if(!match){
                    t++;
                }
            }
        }
        // only stop loop once all contour cells are removed
        while (m_contour_cells.size() > 0);
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
    if (m_path_cells.size() > 0) {
        Cell *c;
        for (int i = 0; i < m_path_cells.size(); ++i) {
            for (int j = 0; j < m_path_cells[i].size(); ++j) {
                c = m_path_cells[i][j];
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

