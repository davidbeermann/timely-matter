#include "KinectModel.hpp"
#include "ofxCv.h"

#define SETTINGS_FILE "KinectModelSettings.xml"

using namespace timelymatter;
using namespace ofxCv;


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
    m_depth_buffer_width = 0;
    m_depth_buffer_height = 0;
    
    m_selection_points.push_back(ofVec2f(0.f, 0.f));
    m_selection_points.push_back(ofVec2f(0.f, 0.f));
    m_selection_points.push_back(ofVec2f(0.f, 0.f));
    m_selection_points.push_back(ofVec2f(0.f, 0.f));
    
    m_cv_selection_points.push_back(Point2f(0.f, 0.f));
    m_cv_selection_points.push_back(Point2f(0.f, 0.f));
    m_cv_selection_points.push_back(Point2f(0.f, 0.f));
    m_cv_selection_points.push_back(Point2f(0.f, 0.f));
    
    m_cv_output_points.push_back(Point2f(0.f, 0.f));
    m_cv_output_points.push_back(Point2f(0.f, 0.f));
    m_cv_output_points.push_back(Point2f(0.f, 0.f));
    m_cv_output_points.push_back(Point2f(0.f, 0.f));
}


KinectModel& KinectModel::get() {
    static KinectModel model;
    return model;
}


shared_ptr<ofxKinect> KinectModel::getKinect() {
    if (!m_kinect_sptr->isConnected()) {
        ofLogNotice("KinectModel") << "Kinect is connected";
        
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
        ofLogError("KinectModel") << "Out of range value for depth clipping near. Must be within [" << m_depth_clip_near_min << "," << m_depth_clip_near_max << "]";
    }
}


void KinectModel::setDepthClipFar(const unsigned int& value) {
    if (value >= m_depth_clip_far_min && value <= m_depth_clip_far_max) {
        m_depth_clip_far = value;
    } else {
        ofLogError("KinectModel") << "Out of range value for depth clipping far. Must be within [" << m_depth_clip_far_min << "," << m_depth_clip_far_max << "]";
    }
}


void KinectModel::setDepthBufferSize(const unsigned int& width, const unsigned int& height) {
    m_depth_buffer_width = width;
    m_depth_buffer_height = height;
    
    m_cv_output_points[1].x = width;
    m_cv_output_points[2].x = width;
    m_cv_output_points[2].y = height;
    m_cv_output_points[3].y = height;
}


void KinectModel::setSelectionPoints(const vector<ofVec2f>& points) {
    for (int i = 0; i < m_selection_points.size(); ++i) {
        m_selection_points[i].set(points[i]);
        
        m_cv_selection_points[i].x = points[i].x;
        m_cv_selection_points[i].y = points[i].y;
    }
}


Mat& KinectModel::getHomographyMatrix() {
    m_homography_matrix = findHomography(Mat(m_cv_selection_points), Mat(m_cv_output_points));
    return m_homography_matrix;
}


Mat& KinectModel::getHomographyMatrix(const vector<Point2f>& source_points) {
    m_homography_matrix = findHomography(Mat(source_points), Mat(m_cv_output_points));
    return m_homography_matrix;
}


void KinectModel::loadSettings() {
    m_settings_loaded = m_settings.loadFile(SETTINGS_FILE);
    if (m_settings_loaded) {
        ofLogNotice("KinectModel") << "settings from file " << SETTINGS_FILE << " loaded";
        
        m_settings.pushTag("KinectModel");
        m_settings.pushTag("selection_points");
        
        int num_tags = m_settings.getNumTags("point");
        if (num_tags != m_selection_points.size()) {
            ofLogWarning("KinectModel") << "Invalid point data detected!";
        } else {
            for (int i = 0; i < num_tags; ++i) {
                m_selection_points[i].x = m_settings.getValue("point:x", 0.f, i);
                m_selection_points[i].y = m_settings.getValue("point:y", 0.f, i);
            }
        }
        
        m_settings.popTag();
        m_settings.popTag();
    }
}


void KinectModel::saveSettings() {
    // remove all nodes in xml settings
    m_settings.clear();
    
    m_settings.addTag("KinectModel");
    m_settings.pushTag("KinectModel");
    m_settings.addTag("selection_points");
    m_settings.pushTag("selection_points");
    for (int i = 0; i < m_selection_points.size(); ++i) {
        int tag = m_settings.addTag("point");
        m_settings.setValue("point:x", m_selection_points[i].x, tag);
        m_settings.setValue("point:y", m_selection_points[i].y, tag);
    }
    m_settings.popTag();
    m_settings.popTag();
    
    // save settings to file
    bool success = m_settings.saveFile(SETTINGS_FILE);
    if (success) {
        ofLogNotice("KinectModel") << "settings successfully written to " << SETTINGS_FILE;
    } else {
        ofLogError("KinectModel") << "settings was unable to write settings to " << SETTINGS_FILE;
    }
}

