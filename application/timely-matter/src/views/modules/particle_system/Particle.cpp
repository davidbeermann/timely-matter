#include "Particle.hpp"
#include "AppConfig.hpp"

#define AREA_ALPHA 0.9
#define CORE_SIZE 3

using namespace timelymatter;


const ofColor Particle::COLOR = ofColor(255, 255, 255, 255);


Particle::Particle(ofParameter<float>& maxVelocity, ofParameter<float>& velocityDecay)
: m_max_velocity(maxVelocity), m_decay(velocityDecay) {
    m_max_velocity_squared = m_max_velocity * m_max_velocity;
    
    m_area_color = COLOR;
    m_area_color.a = 255.f * (float) AREA_ALPHA; // 90% alpha for particle areas
}


void Particle::setup(const ofVec3f & position, const float & radius) {
    m_position = position;
    m_radius = radius;
    m_radius_squared = radius * radius;
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
    
    if (m_position.x < bounds.x + m_radius || m_position.x > bounds.width - m_radius) {
        m_position.x = m_position.x < bounds.x + m_radius ? bounds.x + m_radius : bounds.width - m_radius;
        m_velocity.x *= -1;
    }
    if (m_position.y < bounds.y + m_radius || m_position.y > bounds.height - m_radius) {
        m_position.y = m_position.y < bounds.y + m_radius ? bounds.y + m_radius : bounds.height - m_radius;
        m_velocity.y *= -1;
    }
    
    m_acceleration *= 0;
}


void Particle::draw(const ofVboMesh& mesh) {
    
    drawArea(mesh);
    drawCore(mesh);
    
}


void Particle::drawArea(const ofVboMesh& mesh) {
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(m_position.x, m_position.y);
    
    float scale = m_radius / AppConfig::get().getParticleSystemMaxRadius();
    ofScale(scale, scale);
    ofSetColor(m_area_color);
    mesh.draw();
    
    ofPopStyle();
    ofPopMatrix();
}


void Particle::drawCore(const ofVboMesh& mesh) {
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(m_position.x, m_position.y);
    
    float scale = (float) CORE_SIZE / AppConfig::get().getParticleSystemMaxRadius();
    ofScale(scale, scale);
    ofSetColor(COLOR);
    mesh.draw();
    
    ofPopStyle();
    ofPopMatrix();
}

