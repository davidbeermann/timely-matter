#pragma once

#include "ofMain.h"


class Particle {
    
    ofVec3f m_position;
    ofVec3f m_velocity;
    float m_radius;
    float m_radius_squared;
    
public:
    
    Particle(float x, float y, float r);
    ofVec3f& getPosition();
    ofVec3f& getVelocity();
    const float& getRadius();
    const float& getRadiusSquared();
    
};