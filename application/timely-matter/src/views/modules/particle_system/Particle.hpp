#pragma once

#include "ofMain.h"


namespace timelymatter {
    
    class Particle {
        ofVec3f m_position;
        ofVec3f m_velocity;
        ofVec3f m_acceleration;
        float m_radius;
        float m_radius_squared;
        ofParameter<float>& m_max_velocity;
        ofParameter<float>& m_decay;
        float m_max_velocity_squared;
        ofColor m_area_color;
        
    public:
        static const ofColor COLOR;
        Particle(ofParameter<float>& maxVelocity, ofParameter<float>& velocityDecay);
        void setup(const ofVec3f & position, const float & radius);
        void applyForce(const ofVec3f& force);
        void update(const ofRectangle& bounds);
        void draw(const ofVboMesh& mesh);
        void drawArea(const ofVboMesh& mesh);
        void drawCore(const ofVboMesh& mesh);
        
        const ofVec3f & getPosition() const {
            return m_position;
        }
        
        const float & getRadius() {
            return m_radius;
        }
        
        const float & getRadiusSquared() {
            return m_radius_squared;
        }
    };
    
}

