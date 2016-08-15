#pragma once

#include "ofMain.h"
#include "VectorFieldDirections.h"

// forward declaration for typedefs
class VectorFieldMark;
// specific neighbor typedefs
// http://stackoverflow.com/questions/4088387/how-to-store-pointers-in-map#4088438
typedef map<Directions, VectorFieldMark*> NeighborMap;
typedef pair<Directions, VectorFieldMark*> NeighborMapPair;


class VectorFieldMark {
    unsigned int mID = 0;
    // stores the relative position within the vector field
    ofVec3f mPosition = ofVec3f(0.f, 0.f, 0.f);
    // stores the absolute force based on the measurement at its realtive position.
    ofVec3f mForce = ofVec3f(0.f, 0.f, 0.f);
    // stores the measurement value derived from the vector field input
    float mDatum = 0.f;
    // defines whether the mark has a fixed force
    bool mFixed = false;
    // map to store neighbors for this mark according to their position in the grid
    NeighborMap mNeighbors;
public:
    void setup(unsigned int id, float posX, float posY);
    void setFixed(const ofVec3f& referencePoint, float maxForce);
    void setNeighbor(Directions direction, VectorFieldMark* mark);
    void reset();
    void update();
    void drawDebug();
    const unsigned int& getID();
    const ofVec3f& getPosition();
    const ofVec3f& getForce();
    const float& getDatum();
    const int getNeighborCount();
    const bool hasForce();
    const bool& isFixed();
};