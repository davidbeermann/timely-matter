#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "KinectView.hpp"
#include "VectorFieldInputProvider.h"
#include "AppVars.hpp"



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
    const bool doIsReady();
    // private class attributes
    ofxKinect m_kinect;
    KinectView* m_view;
    ofParameter<bool> mGuiShowDepthImage;
    ofParameter<int> mGuiDepthNearPlane;
    ofParameter<int> mGuiDepthFarPlane;
public:
    ~KinectInputProvider();
};