#pragma once

#include "ofMain.h"
#include "MeterGridUnit.h"
#include "Line.h"

class MarchingSquares {
public:
    static void updateUnits(vector<MeterGridUnit> &units, vector<int> &edgeUnitIndices);
    static void getUnitLines(const vector<MeterGridUnit> &units, vector<Line> &lines);
private:
    static const float OFFSET_LOOKUP[144];
    static const uint8_t FORCES_LOOKUP[16];
    static const ofVec2f FORCES[9];
};
