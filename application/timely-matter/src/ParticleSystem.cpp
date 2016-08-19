#include "ParticleSystem.h"

typedef vector<Particle>::iterator PIt;


void ParticleSystem::setup(const unsigned int numParticles, const ofVec3f size) {
    // define bounding box for particles
    mBounds.set(0, 0, size.x, size.y);
    
    // setup GUI parameters
    mGuiParams.setName("Particle System");
    mGuiParams.add(mGuiShowParticles.set("show particles", true));
    mGuiParams.add(mGuiMaxVelocity.set("max velocity", 5.f, 1.f, 10.f));
    mGuiParams.add(mGuiVelocityDecay.set("velocity decay", 0.99f, 0.9f, 0.999f));
    mGuiParams.add(mGuiShowMarkReference.set("show mark ref", true));
    
    // add particles to system.
    // this has to happen after the GUI setup, due to the max velocity parameter.
    for (unsigned int i = 0; i < numParticles; ++i) {
        Particle p = Particle(mGuiMaxVelocity, mGuiVelocityDecay);
        p.setup(ofVec3f(ofRandom(size.x), ofRandom(size.y), 0.f));
        mParticles.push_back(p);
    }
    
    // create a single mesh for all particles
    mParticleMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    mParticleMesh.addVertex(ofVec3f(0.f, 0.f, 0.f));
    int steps = 12;
    float radius = 3.f;
    double inc = TWO_PI / (double) steps;
    for (int i = 0; i <= steps; ++i) {
        double radian = i * inc;
        mParticleMesh.addVertex(ofVec3f(cos(radian)*radius, sin(radian)*radius, 0.f));
    }
}


void ParticleSystem::applyVectorField(const VectorField& vectorField) {
    if (mGuiShowParticles) {
        for (PIt p = mParticles.begin(); p != mParticles.end(); ++p) {
            ofVec3f force = vectorField.getForceForPosition(p->getPosition());
            p->applyForce(force);
        }
    }
}


void ParticleSystem::update() {
    if (mGuiShowParticles) {
        for (PIt p = mParticles.begin(); p != mParticles.end(); ++p) {
            p->update(mBounds);
        }
    }
}


void ParticleSystem::draw(const VectorField& vectorField) {
    if (mGuiShowParticles) {
        for (PIt p = mParticles.begin(); p != mParticles.end(); ++p) {
            
            p->draw(mParticleMesh);
            
            if(mGuiShowMarkReference) {
                ofVec3f pos = vectorField.getMeterPointForPosition(p->getPosition());
                ofPushStyle();
                ofSetColor(255, 0, 0, 128);
                ofDrawCircle(pos, 5);
                ofPopStyle();
            }
        }
    }
}


const ofParameterGroup& ParticleSystem::getGuiParams() {
    return mGuiParams;
}