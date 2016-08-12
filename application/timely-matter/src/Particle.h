#pragma once

#include "ofMain.h"

class Particle {
    ofVec3f mPosition;
    ofVec3f mVelocity;
    ofVec3f mAcceleration;
    float mMaxVelocity;
    float mMaxVelocitySquared;
    float mDecay;
public:
    void setup(const ofVec3f& position);
    void applyForce(const ofVec3f& force);
    void update(const ofRectangle& bounds);
    void draw();
    const ofVec3f& getPosition();
};