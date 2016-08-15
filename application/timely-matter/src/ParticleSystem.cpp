#include "ParticleSystem.h"

typedef vector<Particle>::iterator PIt;


void ParticleSystem::setup(const unsigned int numParticles, const ofVec3f size) {
    // define bounding box for particles
    mBounds.set(0, 0, size.x, size.y);
    
    // setup GUI parameters
    mGuiParams.setName("Particle System");
    mGuiParams.add(mGuiMaxVelocity.set("max velocity", 5.f, 1.f, 10.f));
    mGuiParams.add(mGuiVelocityDecay.set("velocity decay", 0.99f, 0.9f, 0.999f));
    
    // add particles to system.
    // this has to happen after the GUI setup, due to the max velocity parameter.
    for (unsigned int i = 0; i < numParticles; ++i) {
        Particle p = Particle(mGuiMaxVelocity, mGuiVelocityDecay);
        p.setup(ofVec3f(ofRandom(size.x), ofRandom(size.y), 0.f));
        mParticles.push_back(p);
    }
}


void ParticleSystem::applyVectorField(const VectorField& vectorField) {
    for (PIt p = mParticles.begin(); p != mParticles.end(); ++p) {
        ofVec3f force = vectorField.getForceForPosition(p->getPosition());
        p->applyForce(force);
    }
}


void ParticleSystem::update() {
    for (PIt p = mParticles.begin(); p != mParticles.end(); ++p) {
        p->update(mBounds);
    }
}


void ParticleSystem::draw() {
    for (PIt p = mParticles.begin(); p != mParticles.end(); ++p) {
        p->draw();
    }
}


void ParticleSystem::drawDebug(const VectorField& vectorField) {
    for (PIt p = mParticles.begin(); p != mParticles.end(); ++p) {
        
        p->draw();
        
        ofVec3f pos = vectorField.getMeterPointForPosition(p->getPosition());
        
        ofPushStyle();
        ofSetColor(255, 0, 0, 128);
        ofDrawCircle(pos, 5);
        ofPopStyle();
    }
}


const ofParameterGroup& ParticleSystem::getGuiParams() {
    return mGuiParams;
}