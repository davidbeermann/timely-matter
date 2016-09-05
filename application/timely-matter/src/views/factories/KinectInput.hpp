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
        
        ofParameterGroup m_params;
        
    protected:
        // implementations of abstract class methods
        void m_onWindowResized(const int width, const int height) {};
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
        
        const ofPixels& m_onGetPixels();
        const unsigned int m_onGetWidth();
        const unsigned int m_onGetHeight();
        
        ofParameterGroup& m_onGetParams() {
            return m_params;
        }
        const AppMode m_onGetType() {
            return AppMode::KINECT;
        }
        const string m_onGetName() {
            return "Kinect";
        }
        
    public:
        KinectInput();
        ~KinectInput();
    };

}