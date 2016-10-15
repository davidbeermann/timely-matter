#pragma once

#include "ofMain.h"


class CellUnit {
    
    ofVec3f m_position;
    float m_value;
    
public:
    
    CellUnit(float x, float y);
    void reset();
    const ofVec3f& getPosition();
    void addValue(const float value);
    const float getValue();
    
};