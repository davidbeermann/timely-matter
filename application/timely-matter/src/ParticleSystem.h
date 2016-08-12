#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "VectorField.h"

class ParticleSystem {
    ofRectangle mBounds;
    vector<Particle> mParticles;
public:
    void setup(const unsigned int numParticles, const ofVec3f size);
    void applyVectorField(const VectorField& vectorField);
    void update();
    void draw();
};