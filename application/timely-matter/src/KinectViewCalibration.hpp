#pragma once

#include "ofxOpenCv.h"
#include "KinectView.hpp"
#include "ImageSelection.hpp"


class KinectViewCalibration : public KinectView {
    ImageSelection m_selection;
    ofImage m_kinect_buffer;
    ofxCvGrayscaleImage m_grayscale;
    ofVec2f m_center_position;
    ofParameterGroup m_params;
    ofParameter<float> m_param_norm_min;
    ofParameter<float> m_param_norm_max;
protected:
    void m_onWindowResized(const int width, const int height);
    void m_doSetup();
    void m_doUpdate();
    void m_doDraw();
    const ofParameterGroup& m_doGetParams();
};