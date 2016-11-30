#include "ParticleSystem.hpp"

#define MIN_RADIUS 15
#define MAX_RADIUS 30
#define NUM_COLORS 3

typedef vector<Particle>::iterator PIt;


void ParticleSystem::setup(const unsigned int particle_count) {
    
    float dimension_inc = ofColor::limit() / (float) TWO_PI;
    float angle_inc = (float) TWO_PI / (float) NUM_COLORS;
    float start_angle = ofRandom(TWO_PI);
    
    for (unsigned int i = 0; i < particle_count; ++i) {
        float radius = ofRandom(MIN_RADIUS, MAX_RADIUS);
        float x = ofRandom(radius, ofGetWidth()-radius);
        float y = ofRandom(radius, ofGetHeight()-radius);
        m_particles.push_back(Particle(x, y, radius));
        
        float angle = start_angle + floor(ofRandom(NUM_COLORS + 1)) * angle_inc;
        if (angle > TWO_PI) angle -= TWO_PI;
        float h = angle * dimension_inc;
        float s = ofRandom(0.3f, 0.7f) * ofColor::limit();
        float b = ofRandom(0.3f, 0.7f) * ofColor::limit();
        
        ofColor c;
        c.setHsb(h, s, b);
        m_particles[i].setColor(c);
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
        ofSetColor(p->getColor());
        ofDrawCircle(0.f, 0.f, p->getRadius());
        ofPopStyle();
        
        ofPopMatrix();
    }
}


vector<Particle>& ParticleSystem::getParticles() {
    return m_particles;
}

