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
        ofImage m_depth_source_image;
        ofImage m_depth_output_image;
        cv::Mat m_homography_matrix;
        ofFbo m_fbo;
        ofParameterGroup m_params;
        
    protected:
        // implementations of abstract class methods
        void m_onWindowResized(const int width, const int height) {};
        void m_onSetup();
        void m_onUpdate();
        
        // the draw methods are not needed for this class
        void m_onDraw() {}
        void m_onDraw(const ofRectangle& size) {}
        
        const ofPixels& m_onGetPixels() {
            return m_depth_output_image.getPixels();
        }
        const unsigned int m_onGetWidth() {
            return m_fbo.getWidth();
        }
        const unsigned int m_onGetHeight() {
            return m_fbo.getHeight();
        }
        ofParameterGroup& m_onGetParams() {
            return m_params;
        }
        const AppMode m_onGetType() {
            return AppMode::KINECT;
        }
        const string m_onGetName() {
            return "Kinect";
        }
        ofFbo & m_onGetOutputFbo() {
            return m_fbo;
        };
        
    public:
        KinectInput() {}
        ~KinectInput() {}
    };

}