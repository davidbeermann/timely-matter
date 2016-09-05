#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "VectorFieldInput.hpp"
#include "AppMode.hpp"


namespace timelymatter {

    class KinectInput : public VectorFieldInput {
        
        // private class attributes
        shared_ptr<ofxKinect> m_kinect_sptr;
        cv::Mat m_homographic_matrix;
        
    protected:
        // implementations of abstract class methods
        void m_onWindowResized(const int width, const int height) {};
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
        const ofPixels& m_onGetPixels();
        const unsigned int m_onGetWidth();
        const unsigned int m_onGetHeight();
        const AppMode m_onGetType();
        const string m_onGetName();
        
    public:
        KinectInput();
        ~KinectInput();
    };

}