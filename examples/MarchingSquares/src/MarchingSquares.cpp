#include "MarchingSquares.h"

void MarchingSquares::updateUnits(vector<MeterGridUnit> &units, vector<int> &edgeUnitIndices) {
    // calculate index/weight according to the for corner values
    vector<MeterGridUnit>::iterator unit;
    for (unit = units.begin(); unit != units.end(); ++unit) {
        // initialize index/weight
        uint8_t weight = 0;

        // evaluate corners
        if (unit->getTopLeft().isAboveThreshold()) {
            weight += 0b00001000;
        }
        if (unit->getTopRight().isAboveThreshold()) {
            weight += 0b00000100;
        }
        if (unit->getBottomRight().isAboveThreshold()) {
            weight += 0b00000010;
        }
        if (unit->getBottomLeft().isAboveThreshold()) {
            weight += 0b00000001;
        }

        // update weight and force on unit
        ofVec2f force = FORCES[FORCES_LOOKUP[weight]];
        unit->marchingSquareUpdate(weight, force.x, force.y);

        if(unit->getWeight() > 0 && unit->getWeight() < 15) {
            edgeUnitIndices.push_back(unit->getIndex());
        }
    }
}

void MarchingSquares::getUnitLines(const vector<MeterGridUnit> &units, vector<Line> &lines) {
    vector<MeterGridUnit>::const_iterator unit;
    for (unit = units.begin(); unit != units.end(); ++unit) {
        if (unit->getWeight() > 0 && unit->getWeight() < 15) {
            int startIndex = unit->getWeight() * 9;
            for (int i = startIndex; i < startIndex + 9; i += 4) {
                if (OFFSET_LOOKUP[i] != -1.0f) {
                    lines.push_back(Line(
                            unit->getTopLeft().x() + OFFSET_LOOKUP[i] * unit->getWidth(),
                            unit->getTopLeft().y() + OFFSET_LOOKUP[i + 1] * unit->getHeight(),
                            unit->getTopLeft().x() + OFFSET_LOOKUP[i + 2] * unit->getWidth(),
                            unit->getTopLeft().y() + OFFSET_LOOKUP[i + 3] * unit->getHeight()
                    ));
                }
            }
        }
    }
}

const float MarchingSquares::OFFSET_LOOKUP[144] = {
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 0
        +0.0f, +0.5f, +0.5f, +1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 1
        +0.5f, +1.0f, +1.0f, +0.5f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 2
        +0.0f, +0.5f, +1.0f, +0.5f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 3
        +0.5f, +0.0f, +1.0f, +0.5f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 4
        +0.0f, +0.5f, +0.5f, +0.0f, +0.5f, +1.0f, +1.0f, +0.5f, -1.0f, // 5 (Saddle)
        +0.5f, +0.0f, +0.5f, +1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 6
        +0.0f, +0.5f, +0.5f, +0.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 7
        +0.0f, +0.5f, +0.5f, +0.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 8
        +0.5f, +0.0f, +0.5f, +1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 9
        +0.0f, +0.5f, +0.5f, +1.0f, +0.5f, +0.0f, +1.0f, +0.5f, -1.0f, // 10 (Saddle)
        +0.5f, +0.0f, +1.0f, +0.5f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 11
        +0.0f, +0.5f, +1.0f, +0.5f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 12
        +0.5f, +1.0f, +1.0f, +0.5f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 13
        +0.0f, +0.5f, +0.5f, +1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, // 14
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f  // 15
};

const uint8_t MarchingSquares::FORCES_LOOKUP[16] = {
        0, // 0
        8, // 1
        6, // 2
        7, // 3
        4, // 4
        0, // 5 (Saddle)
        5, // 6
        6, // 7
        2, // 8
        1, // 9
        0, // 10 (Saddle)
        8, // 11
        3, // 12
        2, // 13
        4, // 14
        0  // 15
};

const ofVec2f MarchingSquares::FORCES[9]{
        ofVec2f(0.0f, 0.0f),   // 0 - force: none
        ofVec2f(1.0f, 0.0f),   // 1 - force: right
        ofVec2f(1.0f, 1.0f),  // 2 - force: down right
        ofVec2f(0.0f, 1.0f),  // 3 - force: down
        ofVec2f(-1.0f, 1.0f), // 4 - force: down left
        ofVec2f(-1.0f, 0.0f),  // 5 - force: left
        ofVec2f(-1.0f, -1.0f),  // 6 - force: up left
        ofVec2f(0.0f, -1.0f),   // 7 - force: up
        ofVec2f(1.0f, -1.0f)    // 8 - force: up right
};



