#include "VectorField.hpp"
#include "VectorFieldDirections.hpp"
#include "ParameterUtils.hpp"

using namespace timelymatter;

// Type definition for typing comfort.
typedef vector<VectorFieldMark>::iterator MIt;


void VectorField::setup(const unsigned int width, const unsigned int height, const unsigned int subdivision) {
    setup(width, height, width, height, subdivision, subdivision);
}


void VectorField::setup(const unsigned int width, const unsigned int height, const unsigned int subdivisionX, const unsigned int subdivisionY) {
    setup(width, height, width, height, subdivisionX, subdivisionY);
}


void VectorField::setup(const unsigned int fieldWidth, const unsigned int fieldHeight, const unsigned int inputWidth, const unsigned int inputHeight, const unsigned int subdivision) {
    setup(fieldWidth, fieldHeight, inputWidth, inputHeight, subdivision, subdivision);
}


void VectorField::setup(const unsigned int fieldWidth, const unsigned int fieldHeight, const unsigned int inputWidth, const unsigned int inputHeight, const unsigned int subdivisionX, const unsigned int subdivisionY) {
    // store field configuration
    m_field_width = fieldWidth;
    m_field_height = fieldHeight;
    m_input_width = inputWidth;
    m_input_height = inputHeight;
    m_subdivision_x = subdivisionX;
    m_subdivision_y = subdivisionY;
    
    // setup gui parameters
    // do this now, in order to set the max edge force for fixed marks
    setupVectorFieldParameters(m_params, m_edge_force, m_field_force, m_attract_threshold, m_show_marks, m_show_values, m_show_vectors);
    
    // calculate field increments
    m_field_inc_x = (float) fieldWidth / (float) subdivisionX;
    m_field_inc_y = (float) fieldHeight / (float) subdivisionY;
    // calculate input increments
    m_input_inc_x = (float) inputWidth / (float) subdivisionX;
    m_input_inc_y = (float) inputHeight / (float) subdivisionY;
    
    // add one to each subdivision dimension to include marks at the right and bottom border.
    m_marks_per_row = subdivisionX + 1;
    m_marks_per_column = subdivisionY + 1;
    
    // setup measuring marks
    m_setupMarks();
}


void VectorField::update(const ofPixels &pixels) {
    if (pixels.getWidth() != m_input_width || pixels.getHeight() != m_input_height) {
        ofLog() << "input does not match defined dimensions";
        return;
    }
    
    // reset average datum across all marks
    m_average_datum = 0;
    
    vector<VectorFieldMark>::iterator it;
    for (it = m_marks.begin(); it != m_marks.end(); ++it) {
        // reset force and datum of mark
        it->reset();
        float x = it->getGridPosition().x * m_input_inc_x;
        float y = it->getGridPosition().y * m_input_inc_y;
        // little hack to get values for the last row of pixels
        if (y >= m_input_height) {
            y -= 1;
        }
        // read the value of the red channel - since it is a gray scale image, all channels should have the same value.
        int pixelValue = (int) pixels[(y * m_input_width + x) * pixels.getNumChannels()];
        // update datum
        it->setDatum(pixelValue);
        
        m_average_datum += pixelValue;
    }
    
    // calculate avreage
    m_average_datum /= m_marks.size();
    
    //TODO refactor to one loop!
    for (it = m_marks.begin(); it != m_marks.end(); ++it) {
        it->update(m_field_force, m_edge_force, m_attract_threshold);
    }
}


void VectorField::draw() {
    if (m_show_marks || m_show_values || m_show_vectors) {
        ofPushStyle();
        ofSetLineWidth(0.5f);
        ofNoFill();
        
        MIt mark;
        for (mark = m_marks.begin(); mark != m_marks.end(); ++mark) {
            ofPushStyle();
            ofPushMatrix();
            ofTranslate(mark->getPosition());
            
            if (m_show_marks) {
                ofSetColor(127, 0, 0);
                ofDrawCircle(0, 0, 2);
            }
            
            if (m_show_values) {
                ofSetColor(0, 0, 127);
                ofDrawBitmapString(to_string(mark->getDatum()   ), 0, m_field_inc_y);
            }
            
            if(m_show_vectors && mark->hasForce()) {
                ofSetColor(0, 255, 0);
                ofDrawLine(0, 0, mark->getForce().x, mark->getForce().y);
            }
            
            ofPopMatrix();
            ofPopStyle();
        }
        
        ofPopStyle();
    }
}


const ofVec3f& VectorField::getForceForPosition(const ofVec3f& position) const {
    float relX = round(position.x / m_field_inc_x);
    float relY = round(position.y / m_field_inc_y);
    
    return m_marks[relY * m_marks_per_row + relX].getForce();
}


const ofVec3f VectorField::getMeterPointForPosition(const ofVec3f& position) const {
    float relX = round(position.x / m_field_inc_x);
    float relY = round(position.y / m_field_inc_y);
    
    return ofVec3f(relX * m_field_inc_x, relY * m_field_inc_y, 0.f);
}


void VectorField::m_setupMarks() {
    // setup all measuring marks
    ofVec3f center = ofVec3f(m_field_width * 0.5f, m_field_height * 0.5f);
    for (int y = 0; y < m_marks_per_column; ++y) {
        for (int x = 0; x < m_marks_per_row; ++x) {
            // instantiate new mark
            VectorFieldMark mark;
            
            // calculate unique id for each mark
            unsigned int id = y * m_marks_per_row + x;
            
            // setup mark with id an positions
            mark.setup(id, x * m_field_inc_x, y * m_field_inc_y, x, y);
            
            // identify marks at the outer edges and set them as fixed forces
            if(x == 0 || y == 0 || x == m_subdivision_x || y == m_subdivision_y) {
                mark.setFixed(center);
            }
            
            // store mark in vector
            m_marks.push_back(mark);
        }
    }
    
    // set pointers to neighboring marks
    MIt mark;
    for (mark = m_marks.begin(); mark != m_marks.end(); ++mark) {
        const unsigned int x = mark->getGridPosition().x;
        const unsigned int y = mark->getGridPosition().y;
        
        if (mark->isFixed()) {
            if (x == 0 && y == 0) { // top left corner
                mark->addNeighbor(Directions::EAST, &m_marks[(y) * m_marks_per_row + (x+1)]);
                mark->addNeighbor(Directions::SOUTH_EAST, &m_marks[(y+1) * m_marks_per_row + (x+1)]);
                mark->addNeighbor(Directions::SOUTH, &m_marks[(y+1) * m_marks_per_row + (x)]);
            } else if (x == m_subdivision_x && y == 0) { // top right corner
                mark->addNeighbor(Directions::SOUTH, &m_marks[(y+1) * m_marks_per_row + (x)]);
                mark->addNeighbor(Directions::SOUTH_WEST, &m_marks[(y+1) * m_marks_per_row + (x-1)]);
                mark->addNeighbor(Directions::WEST, &m_marks[(y) * m_marks_per_row + (x-1)]);
            } else if (x == m_subdivision_x && y == m_subdivision_y) { // bottom right corner
                mark->addNeighbor(Directions::WEST, &m_marks[(y) * m_marks_per_row + (x-1)]);
                mark->addNeighbor(Directions::NORTH_WEST, &m_marks[(y-1) * m_marks_per_row + (x-1)]);
                mark->addNeighbor(Directions::NORTH, &m_marks[(y-1) * m_marks_per_row + (x)]);
            } else if (x == 0 && y == m_subdivision_y) { // bottom left corner
                mark->addNeighbor(Directions::NORTH, &m_marks[(y-1) * m_marks_per_row + (x)]);
                mark->addNeighbor(Directions::NORTH_EAST, &m_marks[(y-1) * m_marks_per_row + (x+1)]);
                mark->addNeighbor(Directions::EAST, &m_marks[(y) * m_marks_per_row + (x+1)]);
            } else if (x == 0) { // outer left marks
                mark->addNeighbor(Directions::NORTH, &m_marks[(y-1) * m_marks_per_row + (x)]);
                mark->addNeighbor(Directions::NORTH_EAST, &m_marks[(y-1) * m_marks_per_row + (x+1)]);
                mark->addNeighbor(Directions::EAST, &m_marks[(y) * m_marks_per_row + (x+1)]);
                mark->addNeighbor(Directions::SOUTH_EAST, &m_marks[(y+1) * m_marks_per_row + (x+1)]);
                mark->addNeighbor(Directions::SOUTH, &m_marks[(y+1) * m_marks_per_row + (x)]);
            } else if (x == m_subdivision_x) { // outer right marks
                mark->addNeighbor(Directions::SOUTH, &m_marks[(y+1) * m_marks_per_row + (x)]);
                mark->addNeighbor(Directions::SOUTH_WEST, &m_marks[(y+1) * m_marks_per_row + (x-1)]);
                mark->addNeighbor(Directions::WEST, &m_marks[(y) * m_marks_per_row + (x-1)]);
                mark->addNeighbor(Directions::NORTH_WEST, &m_marks[(y-1) * m_marks_per_row + (x-1)]);
                mark->addNeighbor(Directions::NORTH, &m_marks[(y-1) * m_marks_per_row + (x)]);
            } else if (y == 0) { // outer top marks
                mark->addNeighbor(Directions::EAST, &m_marks[(y) * m_marks_per_row + (x+1)]);
                mark->addNeighbor(Directions::SOUTH_EAST, &m_marks[(y+1) * m_marks_per_row + (x+1)]);
                mark->addNeighbor(Directions::SOUTH, &m_marks[(y+1) * m_marks_per_row + (x)]);
                mark->addNeighbor(Directions::SOUTH_WEST, &m_marks[(y+1) * m_marks_per_row + (x-1)]);
                mark->addNeighbor(Directions::WEST, &m_marks[(y) * m_marks_per_row + (x-1)]);
            } else if (y == m_subdivision_y) {  // outer bottom marks
                mark->addNeighbor(Directions::WEST, &m_marks[(y) * m_marks_per_row + (x-1)]);
                mark->addNeighbor(Directions::NORTH_WEST, &m_marks[(y-1) * m_marks_per_row + (x-1)]);
                mark->addNeighbor(Directions::NORTH, &m_marks[(y-1) * m_marks_per_row + (x)]);
                mark->addNeighbor(Directions::NORTH_EAST, &m_marks[(y-1) * m_marks_per_row + (x+1)]);
                mark->addNeighbor(Directions::EAST, &m_marks[(y) * m_marks_per_row + (x+1)]);
            } else { // no more case left
            }
        } else {
            mark->addNeighbor(Directions::NORTH_WEST, &m_marks[(y-1) * m_marks_per_row + (x-1)]);
            mark->addNeighbor(Directions::NORTH, &m_marks[(y-1) * m_marks_per_row + (x)]);
            mark->addNeighbor(Directions::NORTH_EAST, &m_marks[(y-1) * m_marks_per_row + (x+1)]);
            mark->addNeighbor(Directions::EAST, &m_marks[(y) * m_marks_per_row + (x+1)]);
            mark->addNeighbor(Directions::SOUTH_EAST, &m_marks[(y+1) * m_marks_per_row + (x+1)]);
            mark->addNeighbor(Directions::SOUTH, &m_marks[(y+1) * m_marks_per_row + (x)]);
            mark->addNeighbor(Directions::SOUTH_WEST, &m_marks[(y+1) * m_marks_per_row + (x-1)]);
            mark->addNeighbor(Directions::WEST, &m_marks[(y) * m_marks_per_row + (x-1)]);
        }
        
        //        ofLog() << "mark " << mark->getID() << " has " << mark->getNeighborCount() << " neighbor(s) with neighbor index: " << mark->getNeighborIndex();
    }
}

