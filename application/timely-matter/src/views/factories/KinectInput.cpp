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
    
    m_kinect_sptr->setDepthClipping(m_kinect_model.getDepthClipNear(), m_kinect_model.getDepthClipFar());
    
    m_depth_source_image.allocate(m_kinect_sptr->width, m_kinect_sptr->height, OF_IMAGE_GRAYSCALE);
    m_depth_output_image.allocate(m_kinect_model.getDepthBufferWidth(), m_kinect_model.getDepthBufferHeight(), OF_IMAGE_GRAYSCALE);
    
    m_homography_matrix = findHomography(Mat(m_kinect_model.getCvSelectionPoints()), Mat(m_kinect_model.getCvOutputPoints()));
}


void KinectInput::m_onUpdate() {
    m_kinect_sptr->update();
    
    if (m_kinect_sptr->isFrameNew()) {
        // read depth date into buffer
        m_depth_source_image.setFromPixels(m_kinect_sptr->getDepthPixels());
        
        // extract relevant depth date vis homographic transformation
        warpPerspective(m_depth_source_image, m_depth_output_image, m_homography_matrix, CV_INTER_LINEAR);
        
        // update depth image for drawing
        m_depth_output_image.update();
    }
}


void KinectInput::m_onDraw() {
    
}


const ofPixels& KinectInput::m_onGetPixels() {
    return m_depth_output_image.getPixels();
}


const unsigned int KinectInput::m_onGetWidth() {
    return (unsigned int) m_depth_output_image.getWidth();
}


const unsigned int KinectInput::m_onGetHeight() {
    return (unsigned int) m_depth_output_image.getHeight();
}

