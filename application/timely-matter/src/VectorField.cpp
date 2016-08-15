#include "VectorField.h"
#include "VectorFieldDirections.h"


// Type definition for typing comfort.
// Simply use FIt as type instead of vector<ofVec2f>::iterator when looping over field vectors.
typedef vector<ofVec3f>::iterator FIt;
typedef vector<VectorFieldMark>::iterator MIt;



void VectorField::setup(const int width, const int height, const int subdivision) {
    // store field configuration
    mWidth = width;
    mHeight = height;
    mSubdivision = subdivision;
    
    // calculate field increments
    mIncX = (int) (width / subdivision);
    mIncY = (int) (height / subdivision);
    
    // setup all measuring marks
    ofVec3f center = ofVec3f(width * 0.5f, height * 0.5f);
    for (int y = 0; y <= subdivision; ++y) {
        for (int x = 0; x <= subdivision; ++x) {
            VectorFieldMark mark;
            unsigned int id = y * (subdivision + 1) + x;
            mark.setup(id, x * mIncX, y * mIncY);
            
            if(x == 0 || y == 0 || x == subdivision || y == subdivision) {
                mark.setFixed(center, 12.0f);
            }
            
            mMarks.push_back(mark);
        }
    }
    
    // set pointers to neighboring marks
    int marksPerRow = subdivision + 1; // see setup loop: y <= subdivision; and x <= subdivision;
    for (int y = 1; y < subdivision; ++y) {
        for (int x = 1; x < subdivision; ++x) {
            // This has to be a reference: VectorFieldMark&!!!!
            // Otherwise a copy of the instance in the vector is created!!!!
            VectorFieldMark& mark = mMarks[y * marksPerRow + x];
            
            mark.setNeighbor(Directions::NORTH_WEST, &mMarks[(y-1) * marksPerRow + (x-1)]);
            mark.setNeighbor(Directions::NORTH, &mMarks[(y-1) * marksPerRow + (x)]);
            mark.setNeighbor(Directions::NORTH_EAST, &mMarks[(y-1) * marksPerRow + (x+1)]);
            mark.setNeighbor(Directions::EAST, &mMarks[(y) * marksPerRow + (x+1)]);
            mark.setNeighbor(Directions::SOUTH_EAST, &mMarks[(y+1) * marksPerRow + (x+1)]);
            mark.setNeighbor(Directions::SOUTH, &mMarks[(y+1) * marksPerRow + (x)]);
            mark.setNeighbor(Directions::SOUTH_WEST, &mMarks[(y+1) * marksPerRow + (x-1)]);
            mark.setNeighbor(Directions::WEST, &mMarks[(y) * marksPerRow + (x-1)]);
//            ofLog() << "mark " << mark.getID() << " has " << mark.getNeighborCount() << " neighbor(s)";
        }
    }
    
    
    // calculate total amount of vectors in the field.
    int fieldSize = (mSubdivision - 1) * (mSubdivision - 1);
    
    // fill field with vector instances
    for (int i = 0; i < fieldSize; ++i) {
        mField.push_back(ofVec3f());
    }
    
    // setup gui parameters
    mGuiParams.setName("Vector Field");
    mGuiParams.add(mGuiDebugMeterPoints.set("meter points", false));
    mGuiParams.add(mGuiDebugMeterValues.set("meter values", false));
    mGuiParams.add(mGuiDebugVector.set("vectors", false));
}


void VectorField::setup(const int width, const int height, const int subdivisionX, const int subdivisionY) {
    ofLog() << "This variant of the setup() methos not yet implemented";
}


void VectorField::update(const ofPixels &pixels, const float maxStrength) {
    // reset all field vectors to 0.
    vector<VectorFieldMark>::iterator it;
    for (it = mMarks.begin(); it != mMarks.end(); ++it) {
        it->reset();
    }
    
    
    
    
    
//    // reset all field vectors to 0.
//    clearField();
//    
//    // iterate over all possible vector in field.
//    //
//    for (int y = 1; y <= mSubdivision; ++y) {
//        for (int x = 1; x <= mSubdivision; ++x) {
//            // calculate index of vector in field
//            int fieldIndex = (y - 1) * (mSubdivision - 1) + (x - 1);
//            
//            // calculate all pixel locations of subdivisions: center, top, bottom, right and left.
//            int xPos = x * mIncX;
//            int yPos = y * mIncY;
//            int topPos = (y - 1) * mIncY;
//            int bottomPos = (y + 1) * mIncY;
//            int leftPos = (x - 1) * mIncX;
//            int rightPos = (x + 1) * mIncX;
//            // little hack to get values for the last line of pixels
//            bottomPos = (bottomPos == mHeight) ? bottomPos - 1 : bottomPos;
//            
//            // extract value of red channel for all eight surrounding positions
//            // only the red channel is relevant, since the perlin noise shader writes the same value
//            // into all three channels: red, green, blue – hence the grey scale iamge.
//            int nw = pixels[ (topPos * mWidth + leftPos) * pixels.getNumChannels() ];
//            int n_ = pixels[ (topPos * mWidth + xPos) * pixels.getNumChannels() ];
//            int ne = pixels[ (topPos * mWidth + rightPos) * pixels.getNumChannels() ];
//            int _e = pixels[ (yPos * mWidth + rightPos) * pixels.getNumChannels() ];
//            int se = pixels[ (bottomPos * mWidth + rightPos) * pixels.getNumChannels() ];
//            int s_ = pixels[ (bottomPos * mWidth + xPos) * pixels.getNumChannels() ];
//            int sw = pixels[ (bottomPos * mWidth + leftPos) * pixels.getNumChannels() ];
//            int _w = pixels[ (yPos * mWidth + leftPos) * pixels.getNumChannels() ];
//            
//            //
//            int pixelValue = (int) pixels[(yPos * mWidth + xPos) * pixels.getNumChannels()];
//            
//            // calcualte the difference between all subdivisions at the top and bottom and to the left and right.
//            float diffX = (nw + _w + sw) - (ne + _e + se);
//            float diffY = (nw + n_ + ne) - (sw + s_ + se);
//            
//            // update field position
//            mField[fieldIndex].x = diffX;
//            mField[fieldIndex].y = diffY;
////            if ((float) pixelValue >= 127.5f) {
////                mField[fieldIndex].x = diffX;
////                mField[fieldIndex].y = diffY;
////            } else {
////                mField[fieldIndex].x = -diffX;
////                mField[fieldIndex].y = -diffY;
////            }
//            
//            // apply max strength
//            mField[fieldIndex].normalize();
//            mField[fieldIndex] *= ofMap((float) pixelValue, 0.f, 255.f, 0.f, maxStrength);
////            if ((float) pixelValue >= 127.5f) {
////                mField[fieldIndex] *= ofMap((float) pixelValue, 127.5f, 255.f, 0.f, maxStrength);
////            } else {
////                mField[fieldIndex] *= ofMap((float) pixelValue, 0.f, 127.5f, -maxStrength, 0.f);
////            }
//            
//            // store pixel value in z dimension
//            mField[fieldIndex].z = pixelValue;
//        }
//    }
}


void VectorField::draw() {
    ofPushStyle();
    ofSetLineWidth(0.5f);
    
    MIt mark;
    for (mark = mMarks.begin(); mark != mMarks.end(); ++mark) {
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(mark->getPosition());
        
        ofSetColor(127, 0, 0);
        ofNoFill();
        ofDrawCircle(0, 0, 2);
//        ofDrawBitmapString(to_string(mark->getID()), 0, mIncY);
        
        if(mark->hasForce()) {
            ofSetColor(0, 255, 0);
            ofNoFill();
            ofDrawLine(0, 0, mark->getForce().x, mark->getForce().y);
        }
        
        if(mark->getPosition().x == mIncX * 4 && mark->getPosition().y == mIncY * 7) {
            mark->drawDebug();
        }
        
        ofPopMatrix();
        ofPopStyle();
    }
    
    ofPopStyle();
    
    
//    for (int y = 0; y <= mHeight; y += mIncY) {
//        // little hack to get values for the last line of pixels
//        int yi = (y == mHeight) ? y - 1 : y;
//        
//        for (int x = 0; x <= mWidth; x += mIncX) {
//            
//            int index = (y / mIncY - 1) * (mSubdivision - 1) + (x / mIncX - 1);
//            
//            ofPushStyle();
//            ofPushMatrix();
//            
//            ofSetLineWidth(0.5f);
//            ofTranslate(x, y);
//            
//            if (mGuiDebugMeterPoints) {
//                ofSetColor(127, 0, 0);
//                ofNoFill();
//                ofDrawCircle(0, 0, 2);
//            }
//            
//            if (mGuiDebugMeterValues) {
//                ofSetColor(0, 0, 127);
//                ofPushMatrix();
//                ofScale(0.5f, 0.5f);
//                ofDrawBitmapString(to_string((int) mField[index].z), 0, mIncY);
//                ofPopMatrix();
//            }
//            
//            if (mGuiDebugVector) {
//                if (x > 0 && x < mWidth && y > 0 && y < mHeight) {
//                    ofSetColor(0, 255, 0);
//                    ofNoFill();
//                    ofDrawLine(0, 0, mField[index].x, mField[index].y);
//                }
//            }
//            
//            ofPopMatrix();
//            ofPopStyle();
//        }
//    }
}


const ofVec3f& VectorField::getForceForPosition(const ofVec3f& position) const {
    float relX = round(position.x / (float) mIncX);
    float relY = round(position.y / (float) mIncY);
    
//    ofVec3f tl = mField[floor(relY) * mSubdivision + floor(relX)];
//    ofVec3f tr = mField[floor(relY) * mSubdivision + ceil(relX)];
//    ofVec3f br = mField[ceil(relY) * mSubdivision + ceil(relX)];
//    ofVec3f bl = mField[ceil(relY) * mSubdivision + floor(relX)];
    
    return mField[relY * mSubdivision + relX];
}


const ofVec3f VectorField::getMeterPointForPosition(const ofVec3f& position) const {
    float relX = round(position.x / (float) mIncX);
    float relY = round(position.y / (float) mIncY);    
    return ofVec3f(relX * mIncX, relY * mIncY, 0.f);
}


const ofParameterGroup& VectorField::getGuiParams() {
    return mGuiParams;
}


void VectorField::clearField() {
    for(FIt it = mField.begin(); it != mField.end(); ++it) {
        it->set(0);
    }
}

