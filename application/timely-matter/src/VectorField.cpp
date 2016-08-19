#include "VectorField.h"
#include "VectorFieldDirections.h"


// Type definition for typing comfort.
typedef vector<VectorFieldMark>::iterator MIt;


void VectorField::setup(const unsigned int width, const unsigned int height, const unsigned int subdivision) {
    setup(width, height, subdivision, subdivision);
}


void VectorField::setup(const unsigned int width, const unsigned int height, const unsigned int subdivisionX, const unsigned int subdivisionY) {
    // store field configuration
    mWidth = width;
    mHeight = height;
    mSubdivisionX = subdivisionX;
    mSubdivisionY = subdivisionY;
    
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
    mIncX = (float) width / (float) subdivisionX;
    mIncY = (float) height / (float) subdivisionY;
    
    // add one to each subdivision dimension to include marks at the right and bottom border.
    mMarksPerRow = subdivisionX + 1;
    mMarksPerColumn = subdivisionY + 1;
    
    // setup all measuring marks
    ofVec3f center = ofVec3f(width * 0.5f, height * 0.5f);
    for (int y = 0; y < mMarksPerColumn; ++y) {
        for (int x = 0; x < mMarksPerRow; ++x) {
            // instantiate new mark
            VectorFieldMark mark;
            
            // calculate unique id for each mark
            unsigned int id = y * mMarksPerRow + x;
            
            // setup mark with id an positions
            mark.setup(id, x * mIncX, y * mIncY, x, y);
            
            // identify marks at the outer edges and set them as fixed forces
            if(x == 0 || y == 0 || x == subdivisionX || y == subdivisionY) {
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
            } else if (x == mSubdivisionX && y == 0) { // top right corner
                mark->addNeighbor(Directions::SOUTH, &mMarks[(y+1) * mMarksPerRow + (x)]);
                mark->addNeighbor(Directions::SOUTH_WEST, &mMarks[(y+1) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::WEST, &mMarks[(y) * mMarksPerRow + (x-1)]);
            } else if (x == mSubdivisionX && y == mSubdivisionY) { // bottom right corner
                mark->addNeighbor(Directions::WEST, &mMarks[(y) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::NORTH_WEST, &mMarks[(y-1) * mMarksPerRow + (x-1)]);
                mark->addNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
            } else if (x == 0 && y == mSubdivisionY) { // bottom left corner
                mark->addNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
                mark->addNeighbor(Directions::NORTH_EAST, &mMarks[(y-1) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::EAST, &mMarks[(y) * mMarksPerRow + (x+1)]);
            } else if (x == 0) { // outer left marks
                mark->addNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
                mark->addNeighbor(Directions::NORTH_EAST, &mMarks[(y-1) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::EAST, &mMarks[(y) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::SOUTH_EAST, &mMarks[(y+1) * mMarksPerRow + (x+1)]);
                mark->addNeighbor(Directions::SOUTH, &mMarks[(y+1) * mMarksPerRow + (x)]);
            } else if (x == mSubdivisionX) { // outer right marks
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
            } else if (y == mSubdivisionY) {  // outer bottom marks
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


void VectorField::update(const ofPixels &pixels) {
    
    vector<VectorFieldMark>::iterator it;
    for (it = mMarks.begin(); it != mMarks.end(); ++it) {
        // reset force and datum of mark
        it->reset();
        // little hack to get values for the last row of pixels
        float y = it->getPosition().y >= mHeight ? it->getPosition().y - 1 : it->getPosition().y;
        // read the value of the red channel – since it is a gray scale image, all channels should have the same value.
        int pixelValue = (int) pixels[(y * mWidth + it->getPosition().x) * pixels.getNumChannels()];
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
                ofDrawBitmapString(to_string(mark->getDatum()   ), 0, mIncY);
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
    float relX = round(position.x / mIncX);
    float relY = round(position.y / mIncY);
    
    return mMarks[relY * mMarksPerRow + relX].getForce();
}


const ofVec3f VectorField::getMeterPointForPosition(const ofVec3f& position) const {
    float relX = round(position.x / mIncX);
    float relY = round(position.y / mIncY);
    
    return ofVec3f(relX * mIncX, relY * mIncY, 0.f);
}


const ofParameterGroup& VectorField::getGuiParams() {
    return mGuiParams;
}


void VectorField::onMaxEdgeForceChanged(float& value) {
    ofLog() << value;
}


void VectorField::onMaxFieldForceChanged(float& value) {
    ofLog() << value;
}

