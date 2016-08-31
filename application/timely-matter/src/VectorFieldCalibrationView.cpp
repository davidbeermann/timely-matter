#include "VectorFieldCalibrationView.hpp"
#include "AppModel.hpp"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace cv;
using namespace ofxCv;


void VectorFieldCalibrationView::m_onWindowResized(const int width, const int height) {
    
}


void VectorFieldCalibrationView::m_doSetup() {
    m_selection_fbo.allocate(m_kinect_ptr->width, m_kinect_ptr->height, GL_RGBA, 4);
    m_output_fbo.allocate(m_kinect_ptr->width, m_kinect_ptr->height, GL_RGBA, 4);
    m_kinect_image.allocate(m_kinect_ptr->width, m_kinect_ptr->height, OF_IMAGE_GRAYSCALE);
    m_crop_image.allocate(AppModel::get().getDepthBufferWidth(), AppModel::get().getDepthBufferHeight(), OF_IMAGE_GRAYSCALE);
    
    float fbo_scale = 0.25f;
    m_fbo_output_size.set(0, 0, (int) (m_kinect_ptr->width * fbo_scale), (int) (m_kinect_ptr->height * fbo_scale));
    
    // create path to draw selection overlay
    ofPath path;
    path.setFilled(true);
    path.setFillColor(ofColor(255, 0, 0, 191)); // 75% alpha
    path.moveTo(AppModel::get().getSelectionPoints()[0]);
    path.lineTo(AppModel::get().getSelectionPoints()[1]);
    path.lineTo(AppModel::get().getSelectionPoints()[2]);
    path.lineTo(AppModel::get().getSelectionPoints()[3]);
    path.close();
    
    // draw selection overlay to fbo
    m_selection_fbo.begin();
    ofClear(0);
    path.draw();
    m_selection_fbo.end();
}


void VectorFieldCalibrationView::m_doUpdate() {
    // update output fbo
    m_output_fbo.begin();
    // draw kinect depth output
    m_kinect_ptr->getDepthTexture().draw(0, 0);
    // draw selection overlay
    m_selection_fbo.draw(0, 0);
    m_output_fbo.end();
    
    m_kinect_image.setFromPixels(m_kinect_ptr->getDepthPixels());
    
    Mat matrix = findHomography(Mat(AppModel::get().getOpenCvSelectionPoints()), Mat(AppModel::get().getOpenCvOutputPoints()));
    warpPerspective(m_kinect_image, m_crop_image, matrix, CV_INTER_LINEAR);
}


void VectorFieldCalibrationView::m_doDraw() {
    m_output_fbo.draw(m_fbo_output_size);
    m_crop_image.draw(m_fbo_output_size.x, m_fbo_output_size.y + m_fbo_output_size.height, m_fbo_output_size.width, m_fbo_output_size.height);
}


const ofParameterGroup& VectorFieldCalibrationView::m_doGetParams() {
}

