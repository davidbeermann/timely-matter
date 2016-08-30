#include "KinectCalibrationView.hpp"
#include "ViewEvents.hpp"

#define PADDING 18
#define MARGIN 4


vector<cv::Point2f> KinectCalibrationView::getHomographyPoints() {
    return m_selection.getPoints();
}


void KinectCalibrationView::keyPressed(ofKeyEventArgs& args) {
    if (args.key == OF_KEY_RETURN) {
        ofNotifyEvent(ViewEvents::get().onKinectCalibrated, this);
    }
}


void KinectCalibrationView::m_onWindowResized(const int width, const int height) {
    ofLog() << "KinectCalibrationView::m_onWindowResized()";
    
    ofLog() << m_selection_position;
    m_selection_position.set(PADDING, PADDING);
    ofLog() << m_selection_position;
    m_selection.updatePosition(m_selection_position);
    
//    m_center_position.set((width - m_kinect_ptr->width) * 0.5f, (height - m_kinect_ptr->height) * 0.5f);
}


void KinectCalibrationView::m_doSetup() {
    ofLog() << "KinectCalibrationView::m_doSetup()";
    
    m_selection.setup(m_kinect_ptr->width, m_kinect_ptr->height);
    m_selection.enableMask(false);
    
    m_kinect_buffer.allocate(m_kinect_ptr->width, m_kinect_ptr->height, OF_IMAGE_COLOR);
    m_grayscale.allocate(m_kinect_ptr->width, m_kinect_ptr->height);
    
    m_params.setName("Kinect Calibration");
    ofParameterGroup infrarred_params;
    infrarred_params.setName("Infrarred Normalization");
    infrarred_params.add(m_param_norm_min.set("Min", 33.f, 0.f, 255.f));
    infrarred_params.add(m_param_norm_max.set("Max", 255.f, 0.f, 255.f));
    m_params.add(infrarred_params);
    
    ofNotifyEvent(ViewEvents::get().onParametersChanged, this);
}


void KinectCalibrationView::m_doUpdate() {   
    m_kinect_buffer.setFromPixels(m_kinect_ptr->getPixels());
    m_grayscale = m_kinect_buffer;
    
    // Lighten the grayscale image
    // ---------------------------
    // Solution found here:
    // https://forum.openframeworks.cc/t/levels-with-opencv/1314/6
    cvNormalize(m_grayscale.getCvImage(), m_grayscale.getCvImage(), m_param_norm_min, m_param_norm_max, CV_MINMAX, NULL);
    
    m_selection.getImage().setFromPixels(m_grayscale.getPixels());
}


void KinectCalibrationView::m_doDraw() {
    m_selection.draw();
}


const ofParameterGroup& KinectCalibrationView::m_doGetParams() {
    return m_params;
}

