#pragma once

#include "ofMain.h"
#include "MeterGridPoint.h"

class MeterGridUnit {
public:
    MeterGridUnit(
            const unsigned long index,
            const MeterGridPoint &topLeft,
            const MeterGridPoint &topRight,
            const MeterGridPoint &bottomRight,
            const MeterGridPoint &bottomLeft
    );
    void marchingSquareUpdate(const int weight, const float forceX, const float forceY);
    const MeterGridPoint &getTopLeft() const;
    const MeterGridPoint &getTopRight() const;
    const MeterGridPoint &getBottomRight() const;
    const MeterGridPoint &getBottomLeft() const;
    // http://stackoverflow.com/questions/21492291/strange-member-function-not-viable-error-in-templated-linear-algebra-vector-cl#21492333
    const int &getIndex() const;
    const ofVec2f *getCenter() const;
    const int getWeight() const;
    const ofVec2f getForce() const;
    const int getWidth() const;
    const int getHeight() const;
private:
    const int mIndex;
    const MeterGridPoint &mTopLeft;
    const MeterGridPoint &mTopRight;
    const MeterGridPoint &mBottomRight;
    const MeterGridPoint &mBottomLeft;
    ofVec2f mCenter;
    // stores the value according to the marching square algorithm
    int mWeight;
    ofVec2f mForce;
};
