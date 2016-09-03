#include "KinectModel.hpp"

using namespace timelymatter;


KinectModel::KinectModel() {
    // create shared pointer of kinect instance
    m_kinect_sptr = shared_ptr<ofxKinect>(new ofxKinect());
    // setting default values
    m_depth_clip_near = 1200.f;
    m_depth_clip_far = 1900.f;
}


KinectModel& KinectModel::get() {
    static KinectModel model;
    return model;
}


shared_ptr<ofxKinect> KinectModel::getKinect() {
    if (!m_kinect_sptr->isConnected()) {
        ofLog() << "Connect Kinect";
        
        // Method attributes: init(bool infrared, bool video, bool texture)
        m_kinect_sptr->init(true, true, true);
        
        // calibrates the depth image to align with the rgb image, disabled by default
        // call this before open(), has no effect while the connection is running
        //m_kinect_sptr->setRegistration(true);
        
        // open connection
        m_kinect_sptr->open();
    }
    
    // set the clipping planes for the depth calculations in millimeters
    // you won't get any data < 50cm and distances > 4m start to get noisy
    m_kinect_sptr->setDepthClipping(m_depth_clip_near, m_depth_clip_far);
    
    return m_kinect_sptr;
}


const unsigned int KinectModel::getDepthBufferWidth() const {
    return m_kinect_sptr->width * 0.75;
}


const unsigned int KinectModel::getDepthBufferHeight() const {
    return m_kinect_sptr->height * 0.75;
}

