#pragma once

#include "ofMain.h"

class MeterGridPoint {
public:
    MeterGridPoint(int x, int y, float threshold);
    void update(const ofImage &image);
    int x() const;
    int y() const;
    float threshold() const;
    float reading() const;
    bool isAboveThreshold() const;
private:
    int mX;
    int mY;
    float mThreshold;
    float mReading;
};