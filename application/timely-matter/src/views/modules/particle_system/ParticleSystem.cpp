#include "ParticleSystem.hpp"

#define PARTICLE_MESH_RESOLUTION 36

using namespace timelymatter;

typedef vector<Particle>::iterator PIt;


void ParticleSystem::clearBuffer(ofFbo & fbo) {
    fbo.begin();
    ofClear(0);
    fbo.end();
}


void ParticleSystem::setup(const unsigned int & width, const unsigned int & height, const unsigned int & num_particles, const unsigned int & min_radius, const unsigned int & max_radius) {
    // define bounding box for particles
    m_bounds.set(0, 0, width, height);
    
    // allocate buffers
    m_areas_fbo.allocate(width, height, GL_RGBA, 4);
    m_cores_fbo.allocate(width, height, GL_RGBA, 4);
    m_output_fbo.allocate(width, height, GL_RGBA, 4);
    
    // clear buffers
    clearBuffer(m_areas_fbo);
    clearBuffer(m_cores_fbo);
    clearBuffer(m_output_fbo);
    
    // setup GUI parameters
    m_params.setName("Particle System");
    m_params.add(m_move_particles.set("move particles", true));
    m_params.add(m_show_particles.set("show particles", false));
    m_params.add(m_show_particle_areas.set("show particle areas", true));
    m_params.add(m_show_particle_cores.set("show particle cores", true));
    m_params.add(m_max_velocity.set("max velocity", 5.f, 1.f, 10.f));
    m_params.add(m_velocity_decay.set("velocity decay", 0.99f, 0.9f, 0.999f));
    m_params.add(m_show_mark_reference.set("show mark ref", false));
    m_params.add(m_draw_trail.set("draw trail", false));
    
    // add particles to system.
    // this has to happen after the GUI setup, due to the max velocity parameter.
    for (unsigned int i = 0; i < num_particles; ++i) {
        Particle p = Particle(m_max_velocity, m_velocity_decay);
        p.setup(ofVec3f(ofRandom(width), ofRandom(height), 0.f), ofRandom(min_radius, max_radius));
        m_particles.push_back(p);
    }
    
    // create a single mesh for all particles
    m_particle_mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    m_particle_mesh.addVertex(ofVec3f(0.f, 0.f, 0.f));
    float radius = max_radius;//1.f;
    double inc = TWO_PI / (double) PARTICLE_MESH_RESOLUTION;
    for (int i = 0; i <= (int) PARTICLE_MESH_RESOLUTION; ++i) {
        double radian = i * inc;
        m_particle_mesh.addVertex(ofVec3f(cos(radian)*radius, sin(radian)*radius, 0.f));
    }
}


void ParticleSystem::applyVectorField(VectorField& vectorField) {
    if (m_move_particles) {
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            ofVec3f force = vectorField.getForceForPosition(p->getPosition());
            p->applyForce(force);
        }
    }
}


void ParticleSystem::update() {
    
    // clear buffers of visual components
    clearBuffer(m_areas_fbo);
    clearBuffer(m_cores_fbo);
    
    // evaluate updates
    if (m_move_particles || m_show_particles) {
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            
            if (m_move_particles) {
                p->update(m_bounds);
            }
            
            if (m_show_particles) {
                if (m_show_particle_areas) {
                    m_areas_fbo.begin();
                    p->drawArea(m_particle_mesh);
                    m_areas_fbo.end();
                }
                if (m_show_particle_cores) {
                    m_cores_fbo.begin();
                    p->drawCore(m_particle_mesh);
                    m_cores_fbo.end();
                }
            }
            
        }
    }
    
    // draw output fbo
    m_output_fbo.begin();
    
    // draw trail or clear fbo
    if (m_draw_trail) {
        ofPushStyle();
        ofSetColor(0, 0, 0, 9);
        ofDrawRectangle(0, 0, m_output_fbo.getWidth(), m_output_fbo.getHeight());
        ofPopStyle();
    }
    else {
        ofClear(0);
    }
    
    // draw particle cores on top of particle areas
    m_areas_fbo.draw(0, 0);
    m_cores_fbo.draw(0, 0);
    
    m_output_fbo.end();
}