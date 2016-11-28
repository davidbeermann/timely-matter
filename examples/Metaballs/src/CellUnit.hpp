#pragma once

#include "ofMain.h"


class CellUnit {
    
    ofVec3f m_position;
    float m_value;
    ofColor m_color;
    
public:
    
    CellUnit(float x, float y);
    void reset();
    const ofVec3f& getPosition();
    void addValue(const float value);
    const float getValue();
    const ofColor & getColor();
    void setColor(const ofColor & color);
    
};