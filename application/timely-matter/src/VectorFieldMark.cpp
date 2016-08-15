#include "VectorFieldMark.h"


void VectorFieldMark::setup(unsigned int id, float posX, float posY) {
    mID = id;
    mPosition.set(posX, posY, 0.f);
    mFixed = false;
    
    reset();
}


void VectorFieldMark::setFixed(const ofVec3f& referencePoint, float maxForce) {
    mForce = referencePoint - mPosition;
    mForce.normalize();
    mForce *= maxForce;
    
    mFixed = true;
}


void VectorFieldMark::setNeighbor(Directions direction, VectorFieldMark* mark) {
    mNeighbors.insert(NeighborMapPair(direction, mark));
}


void VectorFieldMark::reset() {
    mForce.set(0.f);
    mDatum = 0;
}


void VectorFieldMark::setDatum(int value) {
    mDatum = value;
}

void VectorFieldMark::update(const float maxStrength) {
    // get measurement readings of all neighboring marks
    const int nw = mNeighbors.at(Directions::NORTH_WEST)->getDatum();
    const int n = mNeighbors.at(Directions::NORTH)->getDatum();
    const int ne = mNeighbors.at(Directions::NORTH_EAST)->getDatum();
    const int e = mNeighbors.at(Directions::EAST)->getDatum();
    const int se = mNeighbors.at(Directions::SOUTH_EAST)->getDatum();
    const int s = mNeighbors.at(Directions::SOUTH)->getDatum();
    const int sw = mNeighbors.at(Directions::SOUTH_WEST)->getDatum();
    const int w = mNeighbors.at(Directions::WEST)->getDatum();
    
    // calculate the difference between all neighbors at the top and bottom and to the left and right.
    int diffX = (nw + w + sw) - (ne + e + se);
    int diffY = (nw + n + ne) - (sw + s + se);
    
    // update force vector
    mForce.set((float) diffX, (float) diffY);
    
    // apply max strength to force vector
    mForce.normalize();
    mForce *= ofMap((float) mDatum, 0.f, 255.f, 0.f, maxStrength);
}


void VectorFieldMark::drawDebug() {
//    ofLog() << "drawDebug() >> mark " << getID() << " has " << getNeighborCount() << " neighbor(s)";
    if (getNeighborCount() == 8) {
        ofPushStyle();
        ofSetColor(0, 128, 0, 128);
        ofFill();
        
        ofVec3f p;
        p = mNeighbors[Directions::NORTH_WEST]->getPosition() - mPosition;
        ofDrawCircle(p.x, p.y, 4);
        p = mNeighbors[Directions::NORTH]->getPosition() - mPosition;
        ofDrawCircle(p.x, p.y, 4);
        p = mNeighbors[Directions::NORTH_EAST]->getPosition() - mPosition;
        ofDrawCircle(p.x, p.y, 4);
        p = mNeighbors[Directions::SOUTH_WEST]->getPosition() - mPosition;
        ofDrawCircle(p.x, p.y, 4);
        p = mNeighbors[Directions::SOUTH]->getPosition() - mPosition;
        ofDrawCircle(p.x, p.y, 4);
        p = mNeighbors[Directions::SOUTH_EAST]->getPosition() - mPosition;
        ofDrawCircle(p.x, p.y, 4);
        
//        NeighborMap::iterator it;
//        for (it = mNeighbors.begin(); it != mNeighbors.end(); ++it) {
//            ofVec3f p = it->second->getPosition() - mPosition;
//            ofDrawCircle(p.x, p.y, 4);
//        }
        
        ofPopStyle();
    }
}


const unsigned int& VectorFieldMark::getID() {
    return mID;
}


const ofVec3f& VectorFieldMark::getPosition() const {
    return mPosition;
}


const ofVec3f& VectorFieldMark::getForce() const {
    return mForce;
}


const int VectorFieldMark::getDatum() {
    return mDatum;
}

const int VectorFieldMark::getNeighborCount() {
    return mNeighbors.size();
}


const bool VectorFieldMark::hasForce() {
    return mForce.x != 0 || mForce.y != 0;
}


const bool& VectorFieldMark::isFixed() {
    return mFixed;
}

