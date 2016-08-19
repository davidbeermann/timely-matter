#pragma once

#include "ofMain.h"

class Particle {
    ofVec3f mPosition;
    ofVec3f mVelocity;
    ofVec3f mAcceleration;
    ofParameter<float>& mMaxVelocity;
    ofParameter<float>& mDecay;
    float mMaxVelocitySquared;
    
public:
    Particle(ofParameter<float>& maxVelocity, ofParameter<float>& velocityDecay);
    void setup(ofVec3f position);
    void applyForce(const ofVec3f& force);
    void update(const ofRectangle& bounds);
    void draw(const ofVboMesh& mesh);
    const ofVec3f& getPosition();
};