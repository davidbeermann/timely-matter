#pragma once

#include "MeterGrid.h"

class DebugView {
    
    ofTrueTypeFont mFont;
    // GUI options
    ofParameterGroup mGuiParameters;
    ofParameter<bool> mDebugMeterPoints;
    ofParameter<bool> mDebugMarchingSquares;
    ofParameter<bool> mDebugIsoLines;
    ofParameter<bool> mDebugForces;
    
public:
    
    DebugView();
    void draw(const vector<MeterGridPoint> &gridPoints, const vector<MeterGridUnit> &gridUnits);
    ofParameterGroup getGuiParameters();

};
