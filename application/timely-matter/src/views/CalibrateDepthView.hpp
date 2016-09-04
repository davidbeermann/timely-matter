#pragma once

#include "BaseView.hpp"
#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "VectorField.hpp"

using namespace cv;


namespace timelymatter
{
    class CalibrateDepthView : public BaseView {
        shared_ptr<ofxKinect> m_kinect_sptr;
        ofVec2f m_center_position;
        ofRectangle m_fbo_output_size;
        ofFbo m_selection_fbo;
        ofFbo m_output_fbo;
        ofImage m_kinect_image;
        ofImage m_depth_image;
        VectorField m_vector_field;
        ofParameterGroup m_params;
        ofParameter<unsigned int> m_param_depth_near;
        ofParameter<unsigned int> m_param_depth_far;
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
    public:
        CalibrateDepthView() : m_kinect_sptr(m_kinect_model.getKinect()) {};
    };
}