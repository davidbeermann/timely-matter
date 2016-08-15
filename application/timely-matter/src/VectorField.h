#pragma once

#include "ofMain.h"
#include "VectorFieldMark.h"

class VectorField {
    int mWidth;
    int mHeight;
    int mSubdivision;
    int mIncX;
    int mIncY;
    vector<ofVec3f> mField;
    vector<VectorFieldMark> mMarks;
    ofParameterGroup mGuiParams;
    ofParameter<bool> mGuiDebugMeterPoints;
    ofParameter<bool> mGuiDebugMeterValues;
    ofParameter<bool> mGuiDebugVector;
    void clearField();
public:
    void setup(const int width, const int height, const int subdivision);
    void setup(const int width, const int height, const int subdivisionX, const int subdivisionY);
    void update(const ofPixels &pixels, const float maxStrength);
    void draw();
    const ofVec3f& getForceForPosition(const ofVec3f& position) const;
    const ofVec3f getMeterPointForPosition(const ofVec3f& position) const;
    const ofParameterGroup& getGuiParams();
};