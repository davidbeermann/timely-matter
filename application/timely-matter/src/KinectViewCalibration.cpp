#include "KinectViewCalibration.hpp"
#include "ofEvents.h"
#include "ViewEvents.hpp"


void KinectViewCalibration::m_onWindowResized(const int width, const int height) {
    ofLog() << "KinectViewCalibration::m_onWindowResized()";
    m_center_position.set((width - m_kinect_ptr->width) * 0.5f, (height - m_kinect_ptr->height) * 0.5f);
}


void KinectViewCalibration::m_doSetup() {
    m_onWindowResized(ofGetWindowWidth(), ofGetWindowHeight());
    
    m_selection.setup(m_center_position, m_kinect_ptr->width, m_kinect_ptr->height);
    m_selection.enableMask(false);
    
    ofNotifyEvent(ViewEvents::get().onParametersChanged, this);
}


void KinectViewCalibration::m_doUpdate() {
    m_selection.update(m_center_position);
    m_selection.getImage().setFromPixels(m_kinect_ptr->getPixels());
}


void KinectViewCalibration::m_doDraw() {
    m_selection.draw();
}


const ofParameterGroup& KinectViewCalibration::m_doGetParams() {
    return m_params;
}

