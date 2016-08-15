#pragma once

#include "ofMain.h"
#include "VectorFieldMark.h"

class VectorField {
    unsigned int mWidth, mHeight;
    unsigned int mSubdivisionX, mSubdivisionY;
    float mIncX, mIncY;
    unsigned int mMarksPerRow, mMarksPerColumn;
    vector<VectorFieldMark> mMarks;
    ofParameterGroup mGuiParams;
    ofParameter<bool> mGuiDebugMeterPoints;
    ofParameter<bool> mGuiDebugMeterValues;
    ofParameter<bool> mGuiDebugVector;
public:
    void setup(const unsigned int width, const unsigned int height, const unsigned int subdivision);
    void setup(const unsigned int width, const unsigned int height, const unsigned int subdivisionX, const unsigned int subdivisionY);
    void update(const ofPixels &pixels, const float maxStrength);
    void draw();
    const ofVec3f& getForceForPosition(const ofVec3f& position) const;
    const ofVec3f getMeterPointForPosition(const ofVec3f& position) const;
    const ofParameterGroup& getGuiParams();
};