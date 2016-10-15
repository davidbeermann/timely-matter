#include "ParticleSystem.hpp"

#define MIN_RADIUS 25
#define MAX_RADIUS 70

typedef vector<Particle>::iterator PIt;


void ParticleSystem::setup(const unsigned int particle_count) {
    for (unsigned int i = 0; i < particle_count; ++i) {
        float radius = ofRandom(MIN_RADIUS, MAX_RADIUS);
        float x = ofRandom(radius, ofGetWidth()-radius);
        float y = ofRandom(radius, ofGetHeight()-radius);
        m_particles.push_back(Particle(x, y, radius));
    }
}


void ParticleSystem::update() {
    for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
        p->getPosition() += p->getVelocity();
        if (p->getPosition().x < p->getRadius() || p->getPosition().x > ofGetWidth() - p->getRadius()) {
            p->getVelocity().x *= -1.f;
            p->getPosition() += p->getVelocity();
        }
        if (p->getPosition().y < p->getRadius() || p->getPosition().y > ofGetHeight() - p->getRadius()) {
            p->getVelocity().y *= -1.f;
            p->getPosition() += p->getVelocity();
        }
    }
}


void ParticleSystem::draw() {
    for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
        ofPushMatrix();
        ofTranslate(p->getPosition());
        
        ofPushStyle();
        ofSetCircleResolution(64);
        ofSetColor(255, 255, 255, 127);
        ofDrawCircle(0.f, 0.f, p->getRadius());
        ofPopStyle();
        
        ofPopMatrix();
    }
}


vector<Particle>& ParticleSystem::getParticles() {
    return m_particles;
}

