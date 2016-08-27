#pragma once

#include "ofMain.h"
#include "VectorFieldInputProvider.h"
#include "AppVars.hpp"
#include "ofxKinect.h"


class KinectInputProvider : public VectorFieldInputProvider {
    // implementations of abstract class methods
    void doSetup();
    void doUpdate();
    void doDraw();
    const ofPixels& doGetPixels();
    const unsigned int doGetWidth();
    const unsigned int doGetHeight();
    const AppMode doGetType();
    const string doGetName();
    // private class attributes
    ofxKinect mKinect;
    ofParameter<bool> mGuiShowDepthImage;
    ofParameter<int> mGuiDepthNearPlane;
    ofParameter<int> mGuiDepthFarPlane;
public:
    ~KinectInputProvider();
};