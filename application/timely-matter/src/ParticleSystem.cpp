#include "ParticleSystem.h"

typedef vector<Particle>::iterator PIt;


void ParticleSystem::setup(const unsigned int numParticles, const ofVec3f size) {
    mBounds.set(0, 0, size.x, size.y);
    
    for (unsigned int i = 0; i < numParticles; ++i) {
        Particle p;
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
