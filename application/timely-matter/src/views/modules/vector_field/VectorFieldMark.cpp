#include "VectorFieldMark.hpp"

using namespace timelymatter;


void VectorFieldMark::setup(unsigned int id, float posX, float posY, unsigned int column, unsigned int row) {
    mID = id;
    mPosition.set(posX, posY, 0.f);
    mGridPosition.set(column, row);
    mFixed = false;
    
    reset();
}


void VectorFieldMark::setFixed(const ofVec3f& referencePoint) {
    mFixedForce = referencePoint - mPosition;
    mFixedForce.normalize();
    
    mFixed = true;
}


void VectorFieldMark::addNeighbor(Directions direction, VectorFieldMark* mark) {
    mNeighborIndex += (unsigned int) direction;
    mNeighbors.insert(NeighborMapPair(direction, mark));
}


void VectorFieldMark::reset() {
    mForce.set(0.f);
    mDatum = 0;
}


void VectorFieldMark::setDatum(int value) {
    mDatum = value;
}

void VectorFieldMark::update(const float& maxFieldForce, const float& maxEdgeForce, const float& attractThreshold) {
    int diffX = 0;
    int diffY = 0;
    int nw, n, ne, e, se, s, sw, w;
    
    switch (mNeighborIndex) {
        case DirectionIndex::TOP_LEFT:
            e = mNeighbors.at(Directions::EAST)->getDatum();
            se = mNeighbors.at(Directions::SOUTH_EAST)->getDatum();
            s = mNeighbors.at(Directions::SOUTH)->getDatum();
            
            diffX = e + se;
            diffY = se + s;
            break;
        case DirectionIndex::TOP_RIGHT:
            s = mNeighbors.at(Directions::SOUTH)->getDatum();
            sw = mNeighbors.at(Directions::SOUTH_WEST)->getDatum();
            w = mNeighbors.at(Directions::WEST)->getDatum();
            
            diffX = -(sw + w);
            diffY = s + sw;
            break;
        case DirectionIndex::BOTTOM_RIGHT:
            w = mNeighbors.at(Directions::WEST)->getDatum();
            nw = mNeighbors.at(Directions::NORTH_WEST)->getDatum();
            n = mNeighbors.at(Directions::NORTH)->getDatum();
            
            diffX = -(w + nw);
            diffY = -(nw + n);
            break;
        case DirectionIndex::BOTTOM_LEFT:
            n = mNeighbors.at(Directions::NORTH)->getDatum();
            ne = mNeighbors.at(Directions::NORTH_EAST)->getDatum();
            e = mNeighbors.at(Directions::EAST)->getDatum();
            
            diffX = ne + e;
            diffY = -(n + ne);
            break;
        case DirectionIndex::TOP_ROW:
            e = mNeighbors.at(Directions::EAST)->getDatum();
            se = mNeighbors.at(Directions::SOUTH_EAST)->getDatum();
            s = mNeighbors.at(Directions::SOUTH)->getDatum();
            sw = mNeighbors.at(Directions::SOUTH_WEST)->getDatum();
            w = mNeighbors.at(Directions::WEST)->getDatum();
            
            diffX = (s + sw + w) - (e + se + s);
            diffY = (se + s + sw);
            break;
        case DirectionIndex::BOTTOM_ROW:
            w = mNeighbors.at(Directions::WEST)->getDatum();
            nw = mNeighbors.at(Directions::NORTH_WEST)->getDatum();
            n = mNeighbors.at(Directions::NORTH)->getDatum();
            ne = mNeighbors.at(Directions::NORTH_EAST)->getDatum();
            e = mNeighbors.at(Directions::EAST)->getDatum();
            
            diffX = (n + ne + e) - (w + nw + n);
            diffY = -(nw + n + ne);
            break;
        case DirectionIndex::LEFT_COLUMN:
            n = mNeighbors.at(Directions::NORTH)->getDatum();
            ne = mNeighbors.at(Directions::NORTH_EAST)->getDatum();
            e = mNeighbors.at(Directions::EAST)->getDatum();
            se = mNeighbors.at(Directions::SOUTH_EAST)->getDatum();
            s = mNeighbors.at(Directions::SOUTH)->getDatum();
            
            diffX = (ne + e + se);
            diffY = (e + se + s) - (n + ne + e);
            break;
        case DirectionIndex::RIGHT_COLUMN:
            s = mNeighbors.at(Directions::SOUTH)->getDatum();
            sw = mNeighbors.at(Directions::SOUTH_WEST)->getDatum();
            w = mNeighbors.at(Directions::WEST)->getDatum();
            nw = mNeighbors.at(Directions::NORTH_WEST)->getDatum();
            n = mNeighbors.at(Directions::NORTH)->getDatum();
            
            diffX = -(sw + w + nw);
            diffY = (s + sw + w) - (w + nw + n);
            break;
        case DirectionIndex::INNER:
            // get measurement readings of all neighboring marks
            nw = mNeighbors.at(Directions::NORTH_WEST)->getDatum();
            n = mNeighbors.at(Directions::NORTH)->getDatum();
            ne = mNeighbors.at(Directions::NORTH_EAST)->getDatum();
            e = mNeighbors.at(Directions::EAST)->getDatum();
            se = mNeighbors.at(Directions::SOUTH_EAST)->getDatum();
            s = mNeighbors.at(Directions::SOUTH)->getDatum();
            sw = mNeighbors.at(Directions::SOUTH_WEST)->getDatum();
            w = mNeighbors.at(Directions::WEST)->getDatum();
            
            // calculate the difference between all neighbors at the top and bottom and to the left and right.
            diffX = (nw + w + sw) - (ne + e + se);
            diffY = (nw + n + ne) - (sw + s + se);
            break;
    }
    
    // update force vector
    mForce.set((float) diffX, (float) diffY);
    
    // apply max strength to force vector
    mForce.normalize();
    
    // decide whether to attract or repell
    if (attractThreshold == 0.f) {
        // all gray-to-white areas repell, only black areas do nothing
        mForce *= ofMap((float) mDatum, 0.f, 255.f, 0.f, maxFieldForce);
    } else if (attractThreshold == 255.f) {
        // all gray-to-black areas attract, only white areas do nothing
        mForce *= ofMap((float) mDatum, 0.f, 255.f, -maxFieldForce, 0.f);
    } else {
        if ((float) mDatum <= attractThreshold) {
            // attract range
            mForce *= ofMap((float) mDatum, 0.f, attractThreshold, -maxFieldForce, 0.f);
        } else {
            // repell range
            mForce *= ofMap((float) mDatum, attractThreshold, 255.f, 0.f, maxFieldForce);
        }
    }
    
    // apply fixed force
    if (mForce.lengthSquared() == 0 && isFixed()) {
        mForce.set(mFixedForce);
        mForce *= maxEdgeForce;
    }
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


const ofVec2f& VectorFieldMark::getGridPosition() const {
    return mGridPosition;
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


const unsigned int VectorFieldMark::getNeighborIndex() {
    return mNeighborIndex;
}


const bool VectorFieldMark::hasForce() {
    return mForce.x != 0 || mForce.y != 0;
}


const bool& VectorFieldMark::isFixed() {
    return mFixed;
}

