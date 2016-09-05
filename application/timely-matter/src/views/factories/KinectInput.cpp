#include "KinectInput.hpp"
#include "ofxCv.h"

using namespace timelymatter;
using namespace ofxCv;
using namespace cv;


KinectInput::KinectInput() {
}


KinectInput::~KinectInput() {
}


void KinectInput::m_onSetup() {
    m_kinect_sptr = m_kinect_model.getKinect();
}


void KinectInput::m_onUpdate() {
    m_kinect_sptr->update();
}


void KinectInput::m_onDraw() {
}


const ofPixels& KinectInput::m_onGetPixels() {
    return m_kinect_sptr->getDepthPixels();
}


const unsigned int KinectInput::m_onGetWidth() {
    return (unsigned int) m_kinect_sptr->getWidth();
}


const unsigned int KinectInput::m_onGetHeight() {
    return (unsigned int) m_kinect_sptr->getHeight();
}

