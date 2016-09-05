#pragma once

#include "ofMain.h"
#include "VectorFieldDirections.hpp"


namespace timelymatter
{

    // forward declaration for typedefs
    class VectorFieldMark;
    // specific neighbor typedefs
    // http://stackoverflow.com/questions/4088387/how-to-store-pointers-in-map#4088438
    typedef map<Directions, VectorFieldMark*> NeighborMap;
    typedef pair<Directions, VectorFieldMark*> NeighborMapPair;


    class VectorFieldMark {
        unsigned int mID = 0;
        // stores the absolute position within the vector field
        ofVec3f mPosition = ofVec3f(0.f, 0.f, 0.f);
        // stores the relative grid position
        ofVec2f mGridPosition = ofVec2f(0.f, 0.f);
        // stores the absolute force based on the measurement at its realtive position.
        ofVec3f mForce = ofVec3f(0.f, 0.f, 0.f);
        // stores the measurement value derived from the vector field input
        int mDatum = 0;
        // defines whether the mark has a fixed force
        bool mFixed = false;
        // fixed force properties
        ofVec3f mFixedForce;
        // map to store neighbors for this mark according to their position in the grid
        NeighborMap mNeighbors;
        // index identifying where in the grid the mark is by its added neighbors
        unsigned int mNeighborIndex = 0;
    public:
        void setup(unsigned int id, float posX, float posY, unsigned int column, unsigned int row);
        void setFixed(const ofVec3f& referencePoint);
        void addNeighbor(Directions direction, VectorFieldMark* mark);
        void setDatum(int value);
        void reset();
        void update(const float& maxFieldForce, const float& maxEdgeForce, const float& attractThreshold);
        void drawDebug();
        const unsigned int& getID();
        const ofVec3f& getPosition() const;
        const ofVec2f& getGridPosition() const;
        const ofVec3f& getForce() const;
        const int getDatum();
        const int getNeighborCount();
        const unsigned int getNeighborIndex();
        const bool hasForce();
        const bool& isFixed();
    };

}