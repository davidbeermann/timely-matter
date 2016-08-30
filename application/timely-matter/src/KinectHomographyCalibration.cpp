#include "KinectHomographyCalibration.hpp"
#include "ViewEvents.hpp"


vector<cv::Point2f> KinectHomographyCalibration::getHomographyPoints() {
    return m_selection.getPoints();
}


void KinectHomographyCalibration::keyPressed(ofKeyEventArgs& args) {
    if (args.key == OF_KEY_RETURN) {
        ofNotifyEvent(ViewEvents::get().onHomographySelected, this);
    }
}


void KinectHomographyCalibration::m_onWindowResized(const int width, const int height) {
    ofLog() << "KinectHomographyCalibration::m_onWindowResized()";
    m_center_position.set((width - m_kinect_ptr->width) * 0.5f, (height - m_kinect_ptr->height) * 0.5f);
}


void KinectHomographyCalibration::m_doSetup() {
//    m_onWindowResized(ofGetWindowWidth(), ofGetWindowHeight());
    
    m_selection.setup(m_center_position, m_kinect_ptr->width, m_kinect_ptr->height);
    m_selection.enableMask(false);
    
    m_kinect_buffer.allocate(m_kinect_ptr->width, m_kinect_ptr->height, OF_IMAGE_COLOR);
    m_grayscale.allocate(m_kinect_ptr->width, m_kinect_ptr->height);
    
    m_params.setName("Homography Calibration");
    m_params.add(m_param_norm_min.set("Normalize Min", 33.f, 0.f, 255.f));
    m_params.add(m_param_norm_max.set("Normalize Max", 255.f, 0.f, 255.f));
    
    ofNotifyEvent(ViewEvents::get().onParametersChanged, this);
}


void KinectHomographyCalibration::m_doUpdate() {
    m_selection.update(m_center_position);
    
    m_kinect_buffer.setFromPixels(m_kinect_ptr->getPixels());
    m_grayscale = m_kinect_buffer;
    
    // Lighten the grayscale image
    // ---------------------------
    // Solution found here:
    // https://forum.openframeworks.cc/t/levels-with-opencv/1314/6
    cvNormalize(m_grayscale.getCvImage(), m_grayscale.getCvImage(), m_param_norm_min, m_param_norm_max, CV_MINMAX, NULL);
    
    m_selection.getImage().setFromPixels(m_grayscale.getPixels());
}


void KinectHomographyCalibration::m_doDraw() {
    m_selection.draw();
}


const ofParameterGroup& KinectHomographyCalibration::m_doGetParams() {
    return m_params;
}

