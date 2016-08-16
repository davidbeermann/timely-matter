#pragma once

#include "ofMain.h"
#include "VectorFieldInputProvider.h"
#include "ofxKinect.h"


class KinectInputProvider : public VectorFieldInputProvider {
private:
    void doSetup();
    void doUpdate();
    void doDraw();
    const ofPixels& doGetPixels();
    ofxKinect mKinect;
    ofParameter<bool> mGuiShowDepthImage;
    ofParameter<int> mGuiDepthNearPlane;
    ofParameter<int> mGuiDepthFarPlane;
};