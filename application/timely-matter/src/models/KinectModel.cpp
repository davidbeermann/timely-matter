#include "KinectModel.hpp"

using namespace timelymatter;


KinectModel::KinectModel() {
    // create shared pointer of kinect instance
    m_kinect_sptr = shared_ptr<ofxKinect>(new ofxKinect());
    
    // set  default values
    m_depth_clip_near = 1200;
    m_depth_clip_near_min = 500;
    m_depth_clip_near_max = 2500;
    m_depth_clip_far = 1900;
    m_depth_clip_far_min = 1000;
    m_depth_clip_far_max = 3000;
    m_depth_buffer_width = m_kinect_sptr->width * 0.75;
    m_depth_buffer_height = m_kinect_sptr->height * 0.75;
    
    m_selection_points.push_back(ofVec2f(0.f, 0.f));
    m_selection_points.push_back(ofVec2f(0.f, 0.f));
    m_selection_points.push_back(ofVec2f(0.f, 0.f));
    m_selection_points.push_back(ofVec2f(0.f, 0.f));
    
    m_cv_selection_points.push_back(Point2f(0.f, 0.f));
    m_cv_selection_points.push_back(Point2f(0.f, 0.f));
    m_cv_selection_points.push_back(Point2f(0.f, 0.f));
    m_cv_selection_points.push_back(Point2f(0.f, 0.f));
    
    m_cv_output_points.push_back(Point2f(0.f, 0.f));
    m_cv_output_points.push_back(Point2f(getDepthBufferWidth(), 0.f));
    m_cv_output_points.push_back(Point2f(getDepthBufferWidth(), getDepthBufferHeight()));
    m_cv_output_points.push_back(Point2f(0.f, getDepthBufferHeight()));
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


void KinectModel::setDepthClipNear(const unsigned int& value) {
    if (value >= m_depth_clip_near_min && value <= m_depth_clip_near_max) {
        m_depth_clip_near = value;
    } else {
        ofLog() << "Out of range value for depth clipping near. Must be within [" << m_depth_clip_near_min << "," << m_depth_clip_near_max << "]";
    }
}


void KinectModel::setDepthClipFar(const unsigned int& value) {
    if (value >= m_depth_clip_far_min && value <= m_depth_clip_far_max) {
        m_depth_clip_far = value;
    } else {
        ofLog() << "Out of range value for depth clipping far. Must be within [" << m_depth_clip_far_min << "," << m_depth_clip_far_max << "]";
    }
}


void KinectModel::setDepthBufferSize(const unsigned int& width, const unsigned int& height) {
    m_depth_buffer_width = width;
    m_depth_buffer_height = height;
}


const unsigned int KinectModel::getDepthBufferWidth() const {
    return m_depth_buffer_width;
}


const unsigned int KinectModel::getDepthBufferHeight() const {
    return m_depth_buffer_height;
}


const vector<ofVec2f>& KinectModel::getSelectionPoints() const {
    return m_selection_points;
}


void KinectModel::setSelectionPoints(const vector<ofVec2f>& points) {
    for (int i = 0; i < m_selection_points.size(); ++i) {
        m_selection_points[i].set(points[i]);
        
        m_cv_selection_points[i].x = points[i].x;
        m_cv_selection_points[i].y = points[i].y;
    }
}


const vector<Point2f>& KinectModel::getCvSelectionPoints() const {
    return m_cv_selection_points;
}


const vector<Point2f>& KinectModel::getCvOutputPoints() const {
    return m_cv_output_points;
}

