#include "Particle.h"


Particle::Particle(ofParameter<float>& maxVelocity, ofParameter<float>& velocityDecay)
: mMaxVelocity(maxVelocity), mDecay(velocityDecay) {
    mMaxVelocitySquared = mMaxVelocity * mMaxVelocity;
}


void Particle::setup(ofVec3f position) {
    mPosition = position;
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


void Particle::draw(const ofVboMesh& mesh) {
    // regular style drawing
//    ofPushStyle();
//    ofSetColor(255);
//    ofDrawCircle(mPosition.x, mPosition.y, 2.5f);
//    ofPopStyle();
    
    // vbo mesh drawing
    ofPushMatrix();
    ofTranslate(mPosition.x, mPosition.y);
    mesh.draw();
    ofPopMatrix();
}


const ofVec3f& Particle::getPosition() {
    return mPosition;
}
