#pragma once

#include "ofMain.h"
#include "KinectView.hpp"


class VectorFieldCalibrationView : public KinectView {
    ofFbo m_selection_fbo;
    ofFbo m_output_fbo;
    ofImage m_kinect_image;
    ofImage m_crop_image;
    ofRectangle m_fbo_output_size;
protected:
    // concrete implementations for AppView
    void m_onWindowResized(const int width, const int height);
    // concrete implementations for KinectView
    void m_doSetup();
    void m_doUpdate();
    void m_doDraw();
    const ofParameterGroup& m_doGetParams();
    
public:
    
};