#include "ParticleSystem.hpp"

#define PARTICLE_MESH_RESOLUTION 36

using namespace timelymatter;

typedef vector<Particle>::iterator PIt;


void ParticleSystem::clearBuffer(ofFbo & fbo) {
    fbo.begin();
    ofClear(m_clear_color);
    fbo.end();
}


void ParticleSystem::setup(const unsigned int & width, const unsigned int & height, const unsigned int & num_particles, const unsigned int & min_radius, const unsigned int & max_radius) {
    // define bounding box for particles
    m_bounds.set(0, 0, width, height);
    
    // allocate buffers
    m_areas_fbo.allocate(width, height, GL_RGBA, 4);
    m_cores_fbo.allocate(width, height, GL_RGBA, 4);
    
    // set color to clear fbos
    m_clear_color = Particle::COLOR;
    m_clear_color.a = 0.f;
    
    // clear buffers
    clearBuffer(m_areas_fbo);
    clearBuffer(m_cores_fbo);
    
    // setup GUI parameters
    m_params.setName("Particle System");
    m_params.add(m_param_max_velocity.set("max velocity", 5.f, 1.f, 10.f));
    m_params.add(m_param_velocity_decay.set("velocity decay", 0.99f, 0.9f, 0.999f));
    m_params.add(m_param_gravity.set("gravity", 0.01f, 0.001f, 0.1f));
    
    // add particles to system.
    // this has to happen after the GUI setup, due to the max velocity parameter.
    for (unsigned int i = 0; i < num_particles; ++i) {
        Particle p = Particle(m_param_max_velocity, m_param_velocity_decay);
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
    // update gravity based on gui
    m_gravity.set(0.f, m_param_gravity, 0.f);
    
    for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
        // apply force from vector field
        ofVec3f field = vectorField.getForceForPosition(p->getPosition());
        p->applyForce(field);
        // apply gravity
        p->applyForce(m_gravity);
    }
}


void ParticleSystem::update() {
    
    // clear buffers of visual components
    clearBuffer(m_areas_fbo);
    clearBuffer(m_cores_fbo);
    
    // evaluate updates
    for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
        
        p->update(m_bounds);

        m_areas_fbo.begin();
        p->drawArea(m_particle_mesh);
        m_areas_fbo.end();

        m_cores_fbo.begin();
        p->drawCore(m_particle_mesh);
        m_cores_fbo.end();
        
    }
}