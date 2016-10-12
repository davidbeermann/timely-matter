#pragma once

#include "ofMain.h"
#include "MeterGridPoint.h"
#include "MeterGridUnit.h"

typedef vector<MeterGridPoint>::iterator ItPoint;


class MeterGrid {
    
    int mColumns = -1;
    int mRows = -1;
    float mThreshold = -1.f;
    vector<MeterGridPoint> mPoints;
    vector<MeterGridUnit> mUnits;
    
public:
    
    MeterGrid() {};
    void setup(const int columns, const int rows, const int resolution, const float threshold);
    void update(const ofImage &image);
    
    vector<MeterGridPoint> &getSamplePoints();
    vector<MeterGridUnit> &getGridUnits();
    vector<MeterGridUnit> *getPointerToGridUnits();
    
};
