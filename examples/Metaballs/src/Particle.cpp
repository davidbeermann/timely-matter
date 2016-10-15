#include "Particle.hpp"


Particle::Particle(float x, float y, float r) {
    m_position.set(x, y);
    m_radius = r;
    m_radius_squared = r * r;
    
    float speed = ofRandom(2, 4);
    float angle = ofRandom(PI * 2.f);
    m_velocity.set(cos(angle) * speed, sin(angle) * speed);
}


ofVec3f& Particle::getPosition() {
    return m_position;
}


ofVec3f& Particle::getVelocity() {
    return m_velocity;
}


const float& Particle::getRadius() {
    return m_radius;
}


const float& Particle::getRadiusSquared() {
    return m_radius_squared;
}