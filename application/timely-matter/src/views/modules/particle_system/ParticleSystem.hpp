#pragma once

#include "ofMain.h"
#include "Particle.hpp"
#include "VectorField.hpp"


namespace timelymatter {
    
    class ParticleSystem {
        
        ofRectangle m_bounds;
        vector<Particle> m_particles;
        ofVboMesh m_particle_mesh;
        ofParameterGroup m_params;
        ofParameter<bool> m_show_particles;
        ofParameter<float> m_max_velocity;
        ofParameter<float> m_velocity_decay;
        ofParameter<bool> m_show_mark_reference;
        
    public:
        void setup(const unsigned int num_particles, const ofVec3f size);
        void applyVectorField(const VectorField& vectorField);
        void update();
        void draw(const VectorField& vectorField);
        
        ofParameterGroup& getParams() { return m_params; }
    };

}

