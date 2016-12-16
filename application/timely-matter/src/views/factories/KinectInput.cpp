#include "KinectInput.hpp"
#include "ofxCv.h"

using namespace timelymatter;
using namespace ofxCv;
using namespace cv;


void KinectInput::m_onSetup() {
    m_kinect_sptr = m_kinect_model.getKinect();
    
    m_kinect_sptr->setDepthClipping(m_kinect_model.getDepthClipNear(), m_kinect_model.getDepthClipFar());
    
    m_depth_source_image.allocate(m_kinect_sptr->width, m_kinect_sptr->height, OF_IMAGE_GRAYSCALE);
    m_depth_output_image.allocate(m_kinect_model.getCropBufferWidth(), m_kinect_model.getCropBufferHeight(), OF_IMAGE_GRAYSCALE);
    
    m_homography_matrix = findHomography(Mat(m_kinect_model.getCvSelectionPoints()), Mat(m_kinect_model.getCvOutputPoints()));
    
    m_fbo.allocate(m_kinect_model.getCropBufferWidth(), m_kinect_model.getCropBufferHeight());
    
    m_params.setName("Kinect Input");
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
        
        // write output image data to fbo
        m_fbo.begin();
        ofClear(0.f);
        m_depth_output_image.draw(0, 0);
        m_fbo.end();
    }
}

