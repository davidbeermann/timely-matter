#pragma once

#include "ofMain.h"
#include "Particle.hpp"


class ParticleSystem {
    
    vector<Particle> m_particles;
    
public:
    
    void setup(const unsigned int particle_count);
    void update();
    void draw();
    vector<Particle>& getParticles();
    
};