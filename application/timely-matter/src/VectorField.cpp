#include "VectorField.h"
#include "VectorFieldDirections.h"


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
    mGuiParams.setName("Vector Field");
    mGuiParams.add(mMaxEdgeForce.set("max edge force", 8.f, 1.f, 12.f));
    mGuiParams.add(mMaxFieldForce.set("max field force", 8.f, 1.f, 12.f));
    mGuiParams.add(mGuiDebugMeterPoints.set("meter points", false));
    mGuiParams.add(mGuiDebugMeterValues.set("meter values", false));
    mGuiParams.add(mGuiDebugVector.set("vectors", false));
    
    // setup listeners for changes in field strength
    //    mMaxEdgeForce.addListener(this, &VectorField::onMaxEdgeForceChanged);
    //    mMaxFieldForce.addListener(this, &VectorField::onMaxFieldForceChanged);
    
    // calculate field increments
    m_field_inc_x = (float) fieldWidth / (float) subdivisionX;
    m_field_inc_y = (float) fieldHeight / (float) subdivisionY;
    // calculate input increments
    m_input_inc_x = (float) inputWidth / (float) subdivisionX;
    m_input_inc_y = (float) inputHeight / (float) subdivisionY;
    
    // add one to each subdivision dimension to include marks at the right and bottom border.
    mMarksPerRow = subdivisionX + 1;
    mMarksPerColumn = subdivisionY + 1;
    
    // setup measuring marks
    m_setupMarks();
}


void VectorField::update(const ofPixels &pixels) {
    if (pixels.getWidth() != m_input_width || pixels.getHeight() != m_input_height) {
        ofLog() << "input does not match defined dimensions";
        return;
    }
    
    vector<VectorFieldMark>::iterator it;
    for (it = mMarks.begin(); it != mMarks.end(); ++it) {
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
    }
    
    //TODO refactor to one loop!
    for (it = mMarks.begin(); it != mMarks.end(); ++it) {
        it->update(mMaxFieldForce, mMaxEdgeForce);
    }
}


void VectorField::draw() {
    if (mGuiDebugMeterPoints || mGuiDebugMeterValues || mGuiDebugVector) {
        ofPushStyle();
        ofSetLineWidth(0.5f);
        ofNoFill();
        
        MIt mark;
        for (mark = mMarks.begin(); mark != mMarks.end(); ++mark) {
            ofPushStyle();
            ofPushMatrix();
            ofTranslate(mark->getPosition());
            
            if (mGuiDebugMeterPoints) {
                ofSetColor(127, 0, 0);
                ofDrawCircle(0, 0, 2);
            }
            
            if (mGuiDebugMeterValues) {
                ofSetColor(0, 0, 127);
                ofDrawBitmapString(to_string(mark->getDatum()   ), 0, m_field_inc_y);
            }
            
            if(mGuiDebugVector && mark->hasForce()) {
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
    
    return mMarks[relY * mMarksPerRow + relX].getForce();
}


const ofVec3f VectorField::getMeterPointForPosition(const ofVec3f& position) const {
    float relX = round(position.x / m_field_inc_x);
    float relY = round(position.y / m_field_inc_y);
    
    return ofVec3f(relX * m_field_inc_x, relY * m_field_inc_y, 0.f);
}


const ofParameterGroup& VectorField::getGuiParams() {
    return mGuiParams;
}


void VectorField::m_setupMarks() {
    // setup all measuring marks
    ofVec3f center = ofVec3f(m_field_width * 0.5f, m_field_height * 0.5f);
    for (int y = 0; y < mMarksPerColumn; ++y) {
        for (int x = 0; x < mMarksPerRow; ++x) {
            // instantiate new mark
            VectorFieldMark mark;
            
            // calculate unique id for each mark
            unsigned int id = y * mMarksPerRow + x;
            
            // setup mark with id an positions
            mark.setup(id, x * m_field_inc_x, y * m_field_inc_y, x, y);
            
            // identify marks at the outer edges and set them as fixed forces
            if(x == 0 || y == 0 || x == m_subdivision_x || y == m_subdivision_y) {
                mark.setFixed(center);
            }
            
            // store mark in vector
            mMarks.push_back(mark);
        }
    }
    
    // set pointers to neighboring marks
    MIt mark;
    for (mark = mMarks.begin(); mark != mMarks.end(); ++mark) {
        const unsigned int x = mark->getGridPosition().x;
        const unsigned int y = mark->getGridPosition().y;
        
        if (mark->isFixed()) {
            if (x == 0 && y == 0) { // top left corner
                mark->addNeighbor(Directions::EAST, &mMarks[(y) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::SOUTH_EAST, &mMarks[(y+1) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::SOUTH, &mMarks[(y+1) * mMarksPerRow + (x)]);
            } else if (x == m_subdivision_x && y == 0) { // top right corner
                mark->addNeighbor(Directions::SOUTH, &mMarks[(y+1) * mMarksPerRow + (x)]);
                mark->addNeighbor(Directions::SOUTH_WEST, &mMarks[(y+1) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::WEST, &mMarks[(y) * mMarksPerRow + (x-1)]);
            } else if (x == m_subdivision_x && y == m_subdivision_y) { // bottom right corner
                mark->addNeighbor(Directions::WEST, &mMarks[(y) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::NORTH_WEST, &mMarks[(y-1) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
            } else if (x == 0 && y == m_subdivision_y) { // bottom left corner
                mark->addNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
                mark->addNeighbor(Directions::NORTH_EAST, &mMarks[(y-1) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::EAST, &mMarks[(y) * mMarksPerRow + (x+1)]);
            } else if (x == 0) { // outer left marks
                mark->addNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
                mark->addNeighbor(Directions::NORTH_EAST, &mMarks[(y-1) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::EAST, &mMarks[(y) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::SOUTH_EAST, &mMarks[(y+1) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::SOUTH, &mMarks[(y+1) * mMarksPerRow + (x)]);
            } else if (x == m_subdivision_x) { // outer right marks
                mark->addNeighbor(Directions::SOUTH, &mMarks[(y+1) * mMarksPerRow + (x)]);
                mark->addNeighbor(Directions::SOUTH_WEST, &mMarks[(y+1) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::WEST, &mMarks[(y) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::NORTH_WEST, &mMarks[(y-1) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
            } else if (y == 0) { // outer top marks
                mark->addNeighbor(Directions::EAST, &mMarks[(y) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::SOUTH_EAST, &mMarks[(y+1) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::SOUTH, &mMarks[(y+1) * mMarksPerRow + (x)]);
                mark->addNeighbor(Directions::SOUTH_WEST, &mMarks[(y+1) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::WEST, &mMarks[(y) * mMarksPerRow + (x-1)]);
            } else if (y == m_subdivision_y) {  // outer bottom marks
                mark->addNeighbor(Directions::WEST, &mMarks[(y) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::NORTH_WEST, &mMarks[(y-1) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
                mark->addNeighbor(Directions::NORTH_EAST, &mMarks[(y-1) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::EAST, &mMarks[(y) * mMarksPerRow + (x+1)]);
            } else { // no more case left
            }
        } else {
            mark->addNeighbor(Directions::NORTH_WEST, &mMarks[(y-1) * mMarksPerRow + (x-1)]);
            mark->addNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
            mark->addNeighbor(Directions::NORTH_EAST, &mMarks[(y-1) * mMarksPerRow + (x+1)]);
            mark->addNeighbor(Directions::EAST, &mMarks[(y) * mMarksPerRow + (x+1)]);
            mark->addNeighbor(Directions::SOUTH_EAST, &mMarks[(y+1) * mMarksPerRow + (x+1)]);
            mark->addNeighbor(Directions::SOUTH, &mMarks[(y+1) * mMarksPerRow + (x)]);
            mark->addNeighbor(Directions::SOUTH_WEST, &mMarks[(y+1) * mMarksPerRow + (x-1)]);
            mark->addNeighbor(Directions::WEST, &mMarks[(y) * mMarksPerRow + (x-1)]);
        }
        
        //        ofLog() << "mark " << mark->getID() << " has " << mark->getNeighborCount() << " neighbor(s) with neighbor index: " << mark->getNeighborIndex();
    }
}


void VectorField::onMaxEdgeForceChanged(float& value) {
    ofLog() << value;
}


void VectorField::onMaxFieldForceChanged(float& value) {
    ofLog() << value;
}

