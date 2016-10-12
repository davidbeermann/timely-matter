#include "MeterGridPoint.h"

MeterGridPoint::MeterGridPoint(int x, int y, float threshold) {
    mX = x;
    mY = y;
    mThreshold = threshold;
}

void MeterGridPoint::update(const ofImage &image) {
    mReading = image.getColor(mX, mY).getBrightness();
}

int MeterGridPoint::x() const {
    return mX;
}

int MeterGridPoint::y() const {
    return mY;
}

float MeterGridPoint::threshold() const {
    return mThreshold;
}

float MeterGridPoint::reading() const {
    return mReading;
}

bool MeterGridPoint::isAboveThreshold() const {
    return mReading >= mThreshold;
}







