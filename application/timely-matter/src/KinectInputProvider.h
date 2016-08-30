#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "KinectView.hpp"
#include "VectorFieldInputProvider.h"
#include "AppVars.hpp"
#include "AppUI.hpp"


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
    void m_doAddParams(AppUI& ui);
    
    // private class methods
    void m_clearView();
    
    // private class attributes
    ofxKinect m_kinect;
    KinectView* m_view;
    cv::Mat m_homographic_matrix;
    
public:
    ~KinectInputProvider();
    void storeCalibration();
};