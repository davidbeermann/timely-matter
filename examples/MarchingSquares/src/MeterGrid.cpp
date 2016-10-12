#include "MeterGrid.h"


void MeterGrid::setup(const int columns, const int rows, const int resolution, const float threshold) {
    // add one to columns and rows to accommodate the for marching squares algorithm

    for (int y = 0; y < rows + 1; ++y) {
        for (int x = 0; x < columns + 1; ++x) {
            // calculate meter point position
            int x_pos = x * resolution;
            int y_pos = y * resolution;
            
            // little hack : move points on the right and bottom 1px in
            if ( x_pos == columns ){
                x_pos -= 1;
            }
            if ( y_pos == rows ){
                y_pos -= 2;
            }
            
            // add meter point to vector
            mPoints.push_back(MeterGridPoint(x_pos, y_pos, threshold));
        }
    }

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            MeterGridUnit gridUnit(
                    mUnits.size(),
                    mPoints[y * (columns + 1) + x],
                    mPoints[y * (columns + 1) + (x + 1)],
                    mPoints[(y + 1) * (columns + 1) + (x + 1)],
                    mPoints[(y + 1) * (columns + 1) + x]
            );
            mUnits.push_back(gridUnit);
        }
    }

    mColumns = columns;
    mRows = rows;
    mThreshold = threshold;
}


void MeterGrid::update(const ofImage &image) {
    // update all readings on meter points
    ItPoint point;
    for (point = mPoints.begin(); point != mPoints.end(); ++point) {
        point->update(image);
    }
}


vector<MeterGridPoint> &MeterGrid::getSamplePoints() {
    return mPoints;
}


vector<MeterGridUnit> &MeterGrid::getGridUnits() {
    return mUnits;
}


vector<MeterGridUnit> *MeterGrid::getPointerToGridUnits() {
    return &mUnits;
}

