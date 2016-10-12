#include "MeterGridUnit.h"

MeterGridUnit::MeterGridUnit(
        const unsigned long index,
        const MeterGridPoint &topLeft,
        const MeterGridPoint &topRight,
        const MeterGridPoint &bottomRight,
        const MeterGridPoint &bottomLeft
) : mIndex((int) index), mTopLeft(topLeft), mTopRight(topRight), mBottomRight(bottomRight), mBottomLeft(bottomLeft)
{
    mCenter = ofVec2f(
            topLeft.x() + (topRight.x() - topLeft.x()) * 0.5f,
            topLeft.y() + (bottomLeft.y() - topLeft.y()) * 0.5f
    );
};

void MeterGridUnit::marchingSquareUpdate(const int weight, const float forceX, const float forceY) {
    mWeight = weight;
    mForce.x = forceX;
    mForce.y = forceY;
};

const MeterGridPoint &MeterGridUnit::getTopLeft() const {
    return mTopLeft;
};

const MeterGridPoint &MeterGridUnit::getTopRight() const {
    return mTopRight;
};

const MeterGridPoint &MeterGridUnit::getBottomRight() const {
    return mBottomRight;
};

const MeterGridPoint &MeterGridUnit::getBottomLeft() const {
    return mBottomLeft;
};

// http://stackoverflow.com/questions/21492291/strange-member-function-not-viable-error-in-templated-linear-algebra-vector-cl#21492333
const int &MeterGridUnit::getIndex() const {
    return mIndex;
}

const ofVec2f *MeterGridUnit::getCenter() const {
    return &mCenter;
};

const int MeterGridUnit::getWeight() const {
    return mWeight;
}

const ofVec2f MeterGridUnit::getForce() const {
    return mForce;
}

const int MeterGridUnit::getWidth() const {
    return mTopRight.x() - mTopLeft.x();
}

const int MeterGridUnit::getHeight() const {
    return mBottomLeft.y() - mTopLeft.y();
}







