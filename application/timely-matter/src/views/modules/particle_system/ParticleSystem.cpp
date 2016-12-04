#include "ParticleSystem.hpp"

using namespace timelymatter;

typedef vector<Particle>::iterator PIt;


void ParticleSystem::setup(const unsigned int & width, const unsigned int & height, const unsigned int & num_particles, const unsigned int & min_radius, const unsigned int & max_radius) {
    // define bounding box for particles
    m_bounds.set(0, 0, width, height);
    
    // allocate buffers
    m_particles_fbo.allocate(width, height);
    m_lines_fbo.allocate(width, height);
    m_output_fbo.allocate(width, height);
    
    // clear buffers
    m_particles_fbo.begin();
    ofClear(0);
    m_particles_fbo.end();
    
    m_lines_fbo.begin();
    ofClear(0);
    m_lines_fbo.end();
    
    m_output_fbo.begin();
    ofClear(0);
    m_output_fbo.end();
    
    // setup lines mesh
    m_lines_mesh.setMode(OF_PRIMITIVE_LINES);
    
    // setup GUI parameters
    m_params.setName("Particle System");
    m_params.add(m_move_particles.set("move particles", true));
    m_params.add(m_show_particles.set("show particles", false));
    m_params.add(m_max_velocity.set("max velocity", 5.f, 1.f, 10.f));
    m_params.add(m_velocity_decay.set("velocity decay", 0.99f, 0.9f, 0.999f));
    m_params.add(m_show_mark_reference.set("show mark ref", false));
    m_params.add(m_draw_lines.set("draw lines", false));
    m_params.add(m_draw_fading.set("draw fading", false));
    
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
    int steps = 12;
    float radius = 1.f;
    double inc = TWO_PI / (double) steps;
    for (int i = 0; i <= steps; ++i) {
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
    if (m_move_particles) {
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            p->update(m_bounds);
        }
    }
}


void ParticleSystem::draw(const VectorField& vectorField) {
    if (m_show_particles) {
        
        m_lines_mesh.clear();
        
        m_particles_fbo.begin();
        ofClear(0);
        
        for (PIt p = m_particles.begin(); p != m_particles.end(); ++p) {
            
            if (m_draw_lines) {
                for (PIt p2 = p + 1; p2 != m_particles.end(); ++p2) {
                    float dist = abs(p->getPosition().distance(p2->getPosition()));
                    if (dist <= 50) {
                        
                        m_lines_mesh.addVertex(p->getPosition());
                        m_lines_mesh.addVertex(p2->getPosition());
                        m_lines_mesh.addColor(ofColor(255));
                        m_lines_mesh.addColor(ofColor(255));
    //                    m_lines_mesh.addColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
    //                    m_lines_mesh.addColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
                    }
                }
            }
            
//            ofPushMatrix();
//            ofScale(p->getRadius()/10, p->getRadius()/10);
            p->draw(m_particle_mesh);
//            ofPopMatrix();
            
            if(m_show_mark_reference) {
                ofVec3f pos = vectorField.getMeterPointForPosition(p->getPosition());
                ofPushStyle();
                ofSetColor(255, 0, 0, 128);
                ofDrawCircle(pos, 5);
                ofPopStyle();
            }
        }
        
        m_particles_fbo.end();
        
        if (m_draw_lines) {
            m_lines_fbo.begin();
            ofClear(0);
            m_lines_mesh.draw();
            m_lines_fbo.end();
        }
        
        m_output_fbo.begin();
        if (m_draw_fading) {
            ofPushStyle();
            ofSetColor(33, 33, 33, 9);
            ofDrawRectangle(0, 0, m_output_fbo.getWidth(), m_output_fbo.getHeight());
            ofPopStyle();
        } else {
            ofClear(0);
        }
        if (m_draw_lines) {
            m_lines_fbo.draw(0, 0);
        }
        m_particles_fbo.draw(0, 0);
        m_output_fbo.end();
        
        m_output_fbo.draw(0, 0);
    }
}