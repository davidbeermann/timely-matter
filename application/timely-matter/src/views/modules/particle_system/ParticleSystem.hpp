#pragma once

#include "ofMain.h"
#include "Particle.hpp"
#include "VectorField.hpp"


namespace timelymatter {
    
    class ParticleSystem {
        
        void clearBuffer(ofFbo & fbo);
        
        ofRectangle m_bounds;
        vector<Particle> m_particles;
        ofVec3f m_gravity;
        ofVboMesh m_particle_mesh;
        ofFbo m_cores_fbo;
        ofFbo m_areas_fbo;
        ofFbo m_output_fbo;
        
        ofParameterGroup m_params;
        ofParameter<bool> m_param_move_particles;
        ofParameter<bool> m_param_show_particles;
        ofParameter<bool> m_param_show_particle_areas;
        ofParameter<bool> m_param_show_particle_cores;
        ofParameter<float> m_param_max_velocity;
        ofParameter<float> m_param_velocity_decay;
        ofParameter<float> m_param_gravity;
        ofParameter<bool> m_param_show_mark_ref;
        ofParameter<bool> m_param_draw_trail;
        
    public:
        void setup(const unsigned int & width, const unsigned int & height, const unsigned int & num_particles, const unsigned int & min_radius, const unsigned int & max_radius);
        void applyVectorField(VectorField& vectorField);
        void update();
        
        ofParameterGroup & getParams() { return m_params; }
        vector<Particle> & getParticles() { return m_particles; }
        ofFbo & getAreasFbo() { return m_areas_fbo; }
        ofFbo & getCoresFbo() { return m_cores_fbo; }
        ofFbo & getOutputFbo() { return m_output_fbo; }
        
    };

}

