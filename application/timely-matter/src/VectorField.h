#pragma once

#include "ofMain.h"

class VectorField {
    int mWidth;
    int mHeight;
    int mSubdivision;
    int mIncX;
    int mIncY;
    vector<ofVec3f> mField;
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
    const ofParameterGroup& getGuiParams();
};