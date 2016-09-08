#include "ParticleSystem.hpp"

using namespace timelymatter;

typedef vector<Particle>::iterator PIt;


void ParticleSystem::setup(const unsigned int num_particles, const ofVec3f size) {
    // define bounding box for particles
    m_bounds.set(0, 0, size.x, size.y);
    
    // setup GUI parameters
    m_params.setName("Particle System");
    m_params.add(m_show_particles.set("show particles", true));
    m_params.add(m_max_velocity.set("max velocity", 5.f, 1.f, 10.f));
    m_params.add(m_velocity_decay.set("velocity decay", 0.99f, 0.9f, 0.999f));
    m_params.add(m_show_mark_reference.set("show mark ref", true));
    
    // add particles to system.
    // this has to happen after the GUI setup, due to the max velocity parameter.
    for (unsigned int i = 0; i < num_particles; ++i) {
        Particle p = Particle(m_max_velocity, m_velocity_decay);
        p.setup(ofVec3f(ofRandom(size.x), ofRandom(size.y), 0.f));
        m_particles.push_back(p);
    }
    
    // create a single mesh for all particles
    m_particle_mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    m_particle_mesh.addVertex(ofVec3f(0.f, 0.f, 0.f));
    int steps = 12;
    float radius = 3.f;
    double inc = TWO_PI / (double) steps;
    for (int i = 0; i <= steps; ++i) {
        double radian = i * inc;
        m_particle_mesh.addVertex(ofVec3f(cos(radian)*radius, sin(radian)*radius, 0.f));
    }
}


void ParticleSystem::applyVectorField(VectorField& vectorField) {
    if (m_show_particles) {
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            ofVec3f force = vectorField.getForceForPosition(p->getPosition());
            p->applyForce(force);
        }
    }
}


void ParticleSystem::update() {
    if (m_show_particles) {
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            p->update(m_bounds);
        }
    }
}


void ParticleSystem::draw(const VectorField& vectorField) {
    if (m_show_particles) {
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            
            p->draw(m_particle_mesh);
            
            if(m_show_mark_reference) {
                ofVec3f pos = vectorField.getMeterPointForPosition(p->getPosition());
                ofPushStyle();
                ofSetColor(255, 0, 0, 128);
                ofDrawCircle(pos, 5);
                ofPopStyle();
            }
        }
    }
}