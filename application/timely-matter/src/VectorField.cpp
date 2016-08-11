#include "VectorField.h"


// Type definition for typing comfort.
// Simply use FIt as type instead of vector<ofVec2f>::iterator when looping over field vectors.
typedef vector<ofVec3f>::iterator FIt;


void VectorField::setup(const int width, const int height, const int subdivision) {
    // store field configuration
    mWidth = width;
    mHeight = height;
    mSubdivision = subdivision;
    
    // calculate field increments
    mIncX = (int) (width / subdivision);
    mIncY = (int) (height / subdivision);
    
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
    clearField();
    
    // iterate over all possible vector in field.
    //
    for (int y = 1; y <= mSubdivision; ++y) {
        for (int x = 1; x <= mSubdivision; ++x) {
            // calculate index of vector in field
            int fieldIndex = (y - 1) * (mSubdivision - 1) + (x - 1);
            
            // calculate all pixel locations of subdivisions: center, top, bottom, right and left.
            int xPos = x * mIncX;
            int yPos = y * mIncY;
            int topPos = (y - 1) * mIncY;
            int bottomPos = (y + 1) * mIncY;
            int leftPos = (x - 1) * mIncX;
            int rightPos = (x + 1) * mIncX;
            // little hack to get values for the last line of pixels
            bottomPos = (bottomPos == mHeight) ? bottomPos - 1 : bottomPos;
            
            // extract value of red channel for all eight surrounding positions
            // only the red channel is relevant, since the perlin noise shader writes the same value
            // into all three channels: red, green, blue – hence the grey scale iamge.
            int nw = pixels[ (topPos * mWidth + leftPos) * pixels.getNumChannels() ];
            int n_ = pixels[ (topPos * mWidth + xPos) * pixels.getNumChannels() ];
            int ne = pixels[ (topPos * mWidth + rightPos) * pixels.getNumChannels() ];
            int _e = pixels[ (yPos * mWidth + rightPos) * pixels.getNumChannels() ];
            int se = pixels[ (bottomPos * mWidth + rightPos) * pixels.getNumChannels() ];
            int s_ = pixels[ (bottomPos * mWidth + xPos) * pixels.getNumChannels() ];
            int sw = pixels[ (bottomPos * mWidth + leftPos) * pixels.getNumChannels() ];
            int _w = pixels[ (yPos * mWidth + leftPos) * pixels.getNumChannels() ];
            
            //
            int pixelValue = (int) pixels[(yPos * mWidth + xPos) * pixels.getNumChannels()];
            
            // calcualte the difference between all subdivisions at the top and bottom and to the left and right.
            float diffX = (nw + _w + sw) - (ne + _e + se);
            float diffY = (nw + n_ + ne) - (sw + s_ + se);
            
            // update field position
            if ((float) pixelValue >= 127.5f) {
                mField[fieldIndex].x = diffX;
                mField[fieldIndex].y = diffY;
            } else {
                mField[fieldIndex].x = -diffX;
                mField[fieldIndex].y = -diffY;
            }
            
            // apply max strength
            mField[fieldIndex].normalize();
            if ((float) pixelValue >= 127.5f) {
                mField[fieldIndex] *= ofMap((float) pixelValue, 127.5f, 255.f, 0.f, maxStrength);
            } else {
                mField[fieldIndex] *= ofMap((float) pixelValue, 0.f, 127.5f, -maxStrength, 0.f);
            }
            
            // store pixel value in z dimension
            mField[fieldIndex].z = pixelValue;
        }
    }
}


void VectorField::draw() {
    // calculate text offset only once
//    float textOffsetY = (FONT_SIZE + mIncY) * 0.5f;
    
    for (int y = 0; y <= mHeight; y += mIncY) {
        // little hack to get values for the last line of pixels
        int yi = (y == mHeight) ? y - 1 : y;
        
        for (int x = 0; x <= mWidth; x += mIncX) {
            
            int index = (y / mIncY - 1) * (mSubdivision - 1) + (x / mIncX - 1);
            
            ofPushStyle();
            ofPushMatrix();
            
            ofSetLineWidth(0.5f);
            ofTranslate(x, y);
            
            if (mGuiDebugMeterPoints) {
                ofSetColor(127, 0, 0);
                ofNoFill();
                ofDrawCircle(0, 0, 2);
            }
            
            if (mGuiDebugMeterValues) {
                ofSetColor(0, 0, 127);
                ofPushMatrix();
                ofScale(0.5f, 0.5f);
                ofDrawBitmapString(to_string((int) mField[index].z), 0, mIncY);
                ofPopMatrix();
            }
            
            if (mGuiDebugVector) {
                if (x > 0 && x < mWidth && y > 0 && y < mHeight) {
                    ofSetColor(0, 255, 0);
                    ofNoFill();
                    ofDrawLine(0, 0, mField[index].x, mField[index].y);
                }
            }
            
            ofPopMatrix();
            ofPopStyle();
        }
    }
}


const ofParameterGroup& VectorField::getGuiParams() {
    return mGuiParams;
}


void VectorField::clearField() {
    for(FIt it = mField.begin(); it != mField.end(); ++it) {
        it->set(0);
    }
}

