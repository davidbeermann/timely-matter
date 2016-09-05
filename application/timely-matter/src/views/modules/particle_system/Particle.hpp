#pragma once

#include "ofMain.h"


namespace timelymatter {
    
    class Particle {
        ofVec3f m_position;
        ofVec3f m_velocity;
        ofVec3f m_acceleration;
        ofParameter<float>& m_max_velocity;
        ofParameter<float>& m_decay;
        float m_max_velocity_squared;
        
    public:
        Particle(ofParameter<float>& maxVelocity, ofParameter<float>& velocityDecay);
        void setup(ofVec3f position);
        void applyForce(const ofVec3f& force);
        void update(const ofRectangle& bounds);
        void draw(const ofVboMesh& mesh);
        const ofVec3f& getPosition();
    };
    
}

