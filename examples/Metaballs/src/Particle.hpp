#pragma once

#include "ofMain.h"


class Particle {
    
    ofColor m_color;
    ofVec3f m_position;
    ofVec3f m_velocity;
    float m_radius;
    float m_radius_squared;
    
public:
    
    Particle(float x, float y, float r);
    void setColor(const ofColor& color);
    void setPosition(const ofVec3f& position);
    const ofColor & getColor();
    ofVec3f& getPosition();
    ofVec3f& getVelocity();
    const float& getRadius();
    const float& getRadiusSquared();
    
};