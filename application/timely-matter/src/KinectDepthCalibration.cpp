#include "KinectDepthCalibration.hpp"
#include "ViewEvents.hpp"
#include "ofxCv.h"

using namespace ofxCv;


const unsigned int KinectDepthCalibration::WIDTH = 256;
const unsigned int KinectDepthCalibration::HEIGHT = 192;


void KinectDepthCalibration::setHomography(const cv::Mat& matrix) {
    // creates a copy of the matrix
    m_homographic_matrix = matrix;
}


void KinectDepthCalibration::m_onWindowResized(const int width, const int height) {
    float margin_x = (width - WIDTH - m_kinect_ptr->width) / 3.f;
    
    m_kinect_position.set(margin_x, (height - m_kinect_ptr->height) * 0.5f);
    m_depth_position.set(margin_x * 2.f + m_kinect_ptr->width, (height - HEIGHT) * 0.5f);
}

void KinectDepthCalibration::m_doSetup() {
    m_kinect_buffer.allocate(m_kinect_ptr->width, m_kinect_ptr->height, OF_IMAGE_GRAYSCALE);
    m_depth_buffer.allocate(WIDTH, HEIGHT, OF_IMAGE_GRAYSCALE);
    
    m_params.setName("Depth Calibration");
    m_params.add(m_param_depth_near.set("near plane", 1000, 500, 2500));
    m_params.add(m_param_depth_far.set("far plane", 2500, 500, 4000));
    
    ofNotifyEvent(ViewEvents::get().onParametersChanged, this);
}


void KinectDepthCalibration::m_doUpdate() {
    // set depth clipping
    // the closer the range the better results for the texture gray values between 0-255.
    m_kinect_ptr->setDepthClipping(m_param_depth_near, m_param_depth_far);
    
    m_kinect_buffer.setFromPixels(m_kinect_ptr->getDepthPixels());
    
    warpPerspective(m_kinect_buffer, m_depth_buffer, m_homographic_matrix, CV_INTER_LINEAR);
    
    m_depth_buffer.update();
}


void KinectDepthCalibration::m_doDraw() {
    m_kinect_buffer.draw(m_kinect_position);
    m_depth_buffer.draw(m_depth_position);
}


const ofParameterGroup& KinectDepthCalibration::m_doGetParams() {
    return m_params;
}

