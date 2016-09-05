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
        ofParameter<unsigned int> m_param_clip_near;
        ofParameter<unsigned int> m_param_clip_far;
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
    public:
        CalibrateDepthView();
        ~CalibrateDepthView();
        // key event listener methods
        void keyPressed(ofKeyEventArgs& args);
        void keyReleased(ofKeyEventArgs& args) {};
    };
}