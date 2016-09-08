#include "Particle.hpp"

using namespace timelymatter;


Particle::Particle(ofParameter<float>& maxVelocity, ofParameter<float>& velocityDecay)
: m_max_velocity(maxVelocity), m_decay(velocityDecay) {
    m_max_velocity_squared = m_max_velocity * m_max_velocity;
}


void Particle::setup(ofVec3f position) {
    m_position = position;
}


void Particle::applyForce(const ofVec3f& force) {
//    ofLog() << "Particle::applyForce() -> force: " << force;
    m_acceleration += force;
}


void Particle::update(const ofRectangle& bounds) {
    
    m_velocity += m_acceleration;
    
    if (m_velocity.lengthSquared() > m_max_velocity_squared) {
        m_velocity = m_velocity.normalize() * m_max_velocity;
    }
    
    m_position += m_velocity;
    
    m_velocity *= m_decay;
    
    if (m_position.x < bounds.x || m_position.x > bounds.width) {
        m_position.x = m_position.x < bounds.x ? bounds.x : bounds.width;
        m_velocity.x *= -1;
    }
    if (m_position.y < bounds.y || m_position.y > bounds.height) {
        m_position.y = m_position.y < bounds.y ? bounds.y : bounds.height;
        m_velocity.y *= -1;
    }
    
    m_acceleration *= 0;
}


void Particle::draw(const ofVboMesh& mesh) {
    // regular style drawing
//    ofPushStyle();
//    ofSetColor(255);
//    ofDrawCircle(m_position.x, m_position.y, 2.5f);
//    ofPopStyle();
    
    // vbo mesh drawing
    ofPushMatrix();
    ofTranslate(m_position.x, m_position.y);
    mesh.draw();
    ofPopMatrix();
}
