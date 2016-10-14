#include "ofApp.h"

#define COUNT 15
#define MIN_RADIUS 20
#define MAX_RADIUS 50
#define X_SEGMENTS 60
#define Y_SEGMENTS 60
#define SEGMENT_SIZE 10

typedef vector<Particle>::iterator PIt;
typedef vector<CellUnit>::iterator CUIt;
typedef vector<Cell>::iterator CIt;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    
    m_particle_count = COUNT;
    
    for (unsigned int i = 0; i < m_particle_count; ++i) {
        float radius = ofRandom(MIN_RADIUS, MAX_RADIUS);
        float x = ofRandom(radius, ofGetWidth()-radius);
        float y = ofRandom(radius, ofGetHeight()-radius);
        m_particles.push_back(Particle(x, y, radius));
    }
    
    for (float y = 0.f; y < Y_SEGMENTS + 1; ++y) {
        for (float x = 0.f; x < X_SEGMENTS + 1; ++x) {
            m_cell_units.push_back(CellUnit(x * SEGMENT_SIZE, y * SEGMENT_SIZE));
        }
    }
    
    for (float y = 0.f; y < Y_SEGMENTS; ++y) {
        for (float x = 0.f; x < X_SEGMENTS; ++x) {
            m_cells.push_back(Cell(SEGMENT_SIZE));
            Cell& cell = m_cells[m_cells.size() - 1];
            
            cell.setTopLeftUnit(&m_cell_units[y * (Y_SEGMENTS + 1) + x]);
            cell.setTopRightUnit(&m_cell_units[y * (Y_SEGMENTS + 1) + (x + 1)]);
            cell.setBottomRightUnit(&m_cell_units[(y + 1) * (Y_SEGMENTS + 1) + (x + 1)]);
            cell.setBottomLeftUnit(&m_cell_units[(y + 1) * (Y_SEGMENTS + 1) + x]);
        }
    }
    
    m_show_gui = false;
    
    m_panel.setup();
    m_panel.setName("Metaballs");
    m_panel.add(m_fitting.set("fitting", 1.f, 0.2f, 1.f));
    m_panel.add(m_show_particles.set("show particles", false));
    m_panel.add(m_move_particles.set("move particles", true));
    m_panel.add(m_show_cells.set("show cells", false));
    m_panel.add(m_show_mesh.set("show mesh", true));
    m_panel.add(m_interpolate.set("interpolate", false));
    m_panel.add(m_infill.set("infill", false));
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(to_string((int) ofGetFrameRate()));
    
    if (m_move_particles) {
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            p->position += p->velocity;
            if (p->position.x < p->radius || p->position.x > ofGetWidth() - p->radius) {
                p->velocity.x *= -1.f;
                p->position += p->velocity;
            }
            if (p->position.y < p->radius || p->position.y > ofGetHeight() - p->radius) {
                p->velocity.y *= -1.f;
                p->position += p->velocity;
            }
        }
    }
    
    for (CUIt cu = m_cell_units.begin(); cu != m_cell_units.end(); ++cu) {
        cu->reset();
        
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            ofVec3f d = p->position - cu->position;
//            float diff = p->radius / d.length();
            float diff = p->radiusSquared / d.lengthSquared();
            
//            if (diff >= m_fitting) {
                cu->value += diff;
//            }
        }
    }
    
    m_mesh.clear();
    
    if (m_infill) {
        m_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    } else {
        m_mesh.setMode(OF_PRIMITIVE_LINES);
    }
    
    if (m_show_mesh) {
        for (CIt c = m_cells.begin(); c != m_cells.end(); ++c) {
            c->updateState();
            c->appendLineVertices(m_mesh, m_interpolate, m_infill);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (m_show_particles) {
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            ofPushMatrix();
            ofTranslate(p->position);
            
            ofPushStyle();
            ofSetCircleResolution(64);
            ofSetColor(255, 255, 255, 127);
            ofDrawCircle(0.f, 0.f, p->radius);
            ofPopStyle();
            
            ofPopMatrix();
        }
    }
    
    if (m_show_cells) {
        for (CUIt cu = m_cell_units.begin(); cu != m_cell_units.end(); ++cu) {
            ofPushMatrix();
            ofTranslate(cu->position);
            
            ofPushStyle();
            ofSetCircleResolution(12);
            if (cu->value < 1.f) {
                ofNoFill();
            }
            ofSetColor(255, 0, 0, 255);
            ofDrawCircle(0.f, 0.f, 3.f);
    //        ofDrawBitmapString(to_string(cu->value), 0.f, 12.f);
            ofPopStyle();
            
            ofPopMatrix();
        }
    }
    
    if (m_show_mesh) {
        m_mesh.draw();
    }
    
    string info = "";
    info += "FPS: " + to_string((int) ofGetFrameRate());
    info += "\nNUM VERTICES: " + to_string((int) m_mesh.getNumVertices());
    if (m_infill) {
        info += "\nNUM TRIANGLES: " + to_string((int) (m_mesh.getNumVertices()/3));
    } else {
        info += "\nNUM LINES: " + to_string((int) (m_mesh.getNumVertices()/2));
    }
    
    ofPushStyle();
    ofSetColor(255, 0, 127, 255);
    ofDrawBitmapString(info, 10, 21);
    ofPopStyle();
    
    if (m_show_gui) {
        m_panel.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'g') {
        m_show_gui = !m_show_gui;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
