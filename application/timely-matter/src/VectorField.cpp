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
            VectorFieldMark mark;
            unsigned int id = y * mMarksPerRow + x;
            mark.setup(id, x * mIncX, y * mIncY);
            
            if(x == 0 || y == 0 || x == subdivisionX || y == subdivisionY) {
                mark.setFixed(center, 8.0f);
            }
            
            mMarks.push_back(mark);
        }
    }
    
    // set pointers to neighboring marks
    for (int y = 1; y < subdivisionY; ++y) {
        for (int x = 1; x < subdivisionX; ++x) {
            // This has to be a reference: VectorFieldMark&!!!!
            // Otherwise a copy of the instance in the vector is created!!!!
            VectorFieldMark& mark = mMarks[y * mMarksPerRow + x];
            
            mark.setNeighbor(Directions::NORTH_WEST, &mMarks[(y-1) * mMarksPerRow + (x-1)]);
            mark.setNeighbor(Directions::NORTH, &mMarks[(y-1) * mMarksPerRow + (x)]);
            mark.setNeighbor(Directions::NORTH_EAST, &mMarks[(y-1) * mMarksPerRow + (x+1)]);
            mark.setNeighbor(Directions::EAST, &mMarks[(y) * mMarksPerRow + (x+1)]);
            mark.setNeighbor(Directions::SOUTH_EAST, &mMarks[(y+1) * mMarksPerRow + (x+1)]);
            mark.setNeighbor(Directions::SOUTH, &mMarks[(y+1) * mMarksPerRow + (x)]);
            mark.setNeighbor(Directions::SOUTH_WEST, &mMarks[(y+1) * mMarksPerRow + (x-1)]);
            mark.setNeighbor(Directions::WEST, &mMarks[(y) * mMarksPerRow + (x-1)]);
//            ofLog() << "mark " << mark.getID() << " has " << mark.getNeighborCount() << " neighbor(s)";
        }
    }
    
    // setup gui parameters
    mGuiParams.setName("Vector Field");
    mGuiParams.add(mGuiDebugMeterPoints.set("meter points", false));
    mGuiParams.add(mGuiDebugMeterValues.set("meter values", false));
    mGuiParams.add(mGuiDebugVector.set("vectors", false));
}


void VectorField::update(const ofPixels &pixels, const float maxStrength) {
    
    vector<VectorFieldMark>::iterator it;
    for (it = mMarks.begin(); it != mMarks.end(); ++it) {
        // only update non fixed vectors
        if (!it->isFixed()) {
            // reset force and datum of mark
            it->reset();
            // update datum
            int pixelValue = (int) pixels[(it->getPosition().y * mWidth + it->getPosition().x) * pixels.getNumChannels()];
            it->setDatum(pixelValue);
        }
    }
    
    //TODO refactor to one loop!
    for (it = mMarks.begin(); it != mMarks.end(); ++it) {
        if (!it->isFixed()) {
            it->update(maxStrength);
        }
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
            
            //        if(mark->getPosition().x == mIncX * 4 && mark->getPosition().y == mIncY * 7) {
            //            mark->drawDebug();
            //        }
            
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

