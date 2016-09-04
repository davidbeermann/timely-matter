#pragma once

#include "BaseView.hpp"
#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ImageSelection.hpp"

using namespace cv;


namespace timelymatter
{
    class CalibrateProjectionView : public BaseView {
        shared_ptr<ofxKinect> m_kinect_sptr;
        ofVec2f m_selection_position;
        ofVec2f m_depth_position;
        ofVec2f m_crop_position;
        ImageSelection m_selection;
        ofImage m_infrared_buffer;
        ofImage m_depth_buffer;
        ofImage m_crop_buffer;
        ofxCvGrayscaleImage m_grayscale;
        Mat m_homographic_matrix;
        ofParameterGroup m_params;
        ofParameter<float> m_param_norm_min;
        ofParameter<float> m_param_norm_max;
        ofParameter<unsigned int> m_param_clip_near;
        ofParameter<unsigned int> m_param_clip_far;
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
    public:
        CalibrateProjectionView();
        ~CalibrateProjectionView();
        // key event listener methods
        void keyPressed(ofKeyEventArgs& args);
        void keyReleased(ofKeyEventArgs& args) {};
    };
}