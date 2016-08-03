#pragma once

#include "ofMain.h"

class VectorField {
public:
    VectorField();
    void setup(const int width, const int height, const int subdivision);
    void update(const ofPixels &pixels, const float maxStrength);
    void draw();
    const ofParameterGroup& getGuiParams();
private:
    const int FONT_SIZE = 6;
    ofTrueTypeFont mFont;
    int mWidth;
    int mHeight;
    int mSubdivision;
    int mIncX;
    int mIncY;
    vector<ofVec3f> mField;
    ofParameterGroup mGuiGroup;
    ofParameter<bool> mGuiDebugMeterPoints;
    ofParameter<bool> mGuiDebugMeterValues;
    ofParameter<bool> mGuiDebugVector;
    void clearField();
};