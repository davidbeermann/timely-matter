#include "KinectModel.hpp"

using namespace timelymatter;


KinectModel& KinectModel::get() {
    static KinectModel model;
    return model;
}


ofxKinect& KinectModel::getKinect() {
    if (!m_kinect.isConnected()) {
        // Method attributes: init(bool infrared, bool video, bool texture)
        m_kinect.init(true, true, true);
        
        // calibrates the depth image to align with the rgb image, disabled by default
        // call this before open(), has no effect while the connection is running
        //m_kinect.setRegistration(true);
        
        // open connection
        m_kinect.open();
    }
    
    // set the clipping planes for the depth calculations in millimeters
    // you won't get any data < 50cm and distances > 4m start to get noisy
    m_kinect.setDepthClipping(m_depth_clip_near, m_depth_clip_far);
    
    return m_kinect;
}


KinectModel::KinectModel() {
    // setting default values
    m_depth_clip_near = 1200.f;
    m_depth_clip_far = 1900.f;
}