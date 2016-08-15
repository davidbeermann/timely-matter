#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "VectorField.h"

class ParticleSystem {
    ofRectangle mBounds;
    vector<Particle> mParticles;
    ofParameterGroup mGuiParams;
    ofParameter<float> mGuiMaxVelocity;
    ofParameter<float> mGuiVelocityDecay;
public:
    void setup(const unsigned int numParticles, const ofVec3f size);
    void applyVectorField(const VectorField& vectorField);
    void update();
    void draw();
    void drawDebug(const VectorField& vectorField);
    const ofParameterGroup& getGuiParams();
};