#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "KinectView.hpp"


class KinectDepthCalibration : public KinectView {
    cv::Mat m_homographic_matrix;
    ofVec2f m_kinect_position;
    ofVec2f m_depth_position;
    ofImage m_kinect_buffer;
    ofImage m_depth_buffer;
    ofParameterGroup m_params;
    ofParameter<int> m_param_depth_near;
    ofParameter<int> m_param_depth_far;
protected:
    void m_onWindowResized(const int width, const int height);
    void m_doSetup();
    void m_doUpdate();
    void m_doDraw();
    const ofParameterGroup& m_doGetParams();
    
public:
    static const unsigned int WIDTH;
    static const unsigned int HEIGHT;
    
    KinectDepthCalibration() {
        ofLog() << "SAY WHAT?!";
    }
    
    void setHomography(const cv::Mat& matrix);
    
};