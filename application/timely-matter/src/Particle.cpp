#include "Particle.h"


void Particle::setup(const ofVec3f& position) {
    mPosition.set(position);
    
    mMaxVelocity = 50.0f;
    mMaxVelocitySquared = mMaxVelocity * mMaxVelocity;
    mDecay = 0.99f;
}


void Particle::applyForce(const ofVec3f& force) {
//    ofLog() << "Particle::applyForce() -> force: " << force;
    mAcceleration += force;
}


void Particle::update(const ofRectangle& bounds) {
    
    mVelocity += mAcceleration;
    
    if (mVelocity.lengthSquared() > mMaxVelocitySquared) {
        mVelocity = mVelocity.normalize() * mMaxVelocity;
    }
    
    mPosition += mVelocity;
    
    mVelocity *= mDecay;
    
    if (mPosition.x < bounds.x || mPosition.x > bounds.width) {
        mPosition.x = mPosition.x < bounds.x ? bounds.x : bounds.width;
        mVelocity.x *= -1;
    }
    if (mPosition.y < bounds.y || mPosition.y > bounds.height) {
        mPosition.y = mPosition.y < bounds.y ? bounds.y : bounds.height;
        mVelocity.y *= -1;
    }
    
    mAcceleration *= 0;
}


void Particle::draw() {
    ofPushStyle();
    ofSetColor(255);
    
//    ofPushMatrix();
    ofDrawCircle(mPosition.x, mPosition.y, 5);
//    ofPopMatrix();
    
    ofPopStyle();
}


const ofVec3f& Particle::getPosition() {
    return mPosition;
}
