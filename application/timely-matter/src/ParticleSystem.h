#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "VectorField.h"

class ParticleSystem {
    ofRectangle mBounds;
    vector<Particle> mParticles;
    ofVboMesh mParticleMesh;
    ofParameterGroup mGuiParams;
    ofParameter<bool> mGuiShowParticles;
    ofParameter<float> mGuiMaxVelocity;
    ofParameter<float> mGuiVelocityDecay;
    ofParameter<bool> mGuiShowMarkReference;
public:
    void setup(const unsigned int numParticles, const ofVec3f size);
    void applyVectorField(const VectorField& vectorField);
    void update();
    void draw(const VectorField& vectorField);
    const ofParameterGroup& getGuiParams();
};