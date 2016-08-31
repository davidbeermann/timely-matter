#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

using namespace cv;


// Class adapted from proposed singleton class found here:
// http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
class AppModel {
private:
    // private constructor
    AppModel() {
        m_output_points_cv.push_back(Point2f());
        m_output_points_cv.push_back(Point2f());
        m_output_points_cv.push_back(Point2f());
        m_output_points_cv.push_back(Point2f());
        
        m_updateDepthBufferSize(m_projector_width / 2, m_projector_height / 2);
    };
    void m_updateDepthBufferSize(const unsigned int width, const unsigned int height) {
        //TODO add buffer size check for larger projectors
        // should not be bigger than (80% ?) of camera size and match aspect ratio
        
        m_depth_buffer_width = width;
        m_depth_buffer_height = height;
        
        m_output_points_cv[0].x = 0;
        m_output_points_cv[0].y = 0;
        
        m_output_points_cv[1].x = width;
        m_output_points_cv[1].y = 0;
        
        m_output_points_cv[2].x = width;
        m_output_points_cv[2].y = height;
        
        m_output_points_cv[3].x = 0;
        m_output_points_cv[3].y = height;
    }
    // camera properties - Kinect 360 resolution
    unsigned int m_camera_width = 640;
    unsigned int m_camera_height = 480;
    // projector properties
    unsigned int m_projector_width = 1024;
    unsigned int m_projector_height = 768;
    // depth buffer properties
    unsigned int m_depth_buffer_width;
    unsigned int m_depth_buffer_height;
    // projector calibration
    vector<ofVec2f> m_selection_points;
    vector<Point2f> m_selection_points_cv;
    vector<Point2f> m_output_points_cv;
    Mat m_homographic_matrix;
public:
    static AppModel& get() {
        static AppModel instance;
        return instance;
    }
    // Remove copy constructor and assignment operator
    // C++ 11 style
    AppModel(AppModel const&) = delete;
    void operator=(AppModel const&) = delete;
    // getter/setter
    void setProjectorSize(const unsigned int width, const unsigned int height) {
        m_projector_width = width;
        m_projector_height = height;
        
        m_updateDepthBufferSize(width / 2, height / 2);
    };
    const ofRectangle getProjectorSize() {
        return ofRectangle(0, 0, m_projector_width, m_projector_height);
    };
    const unsigned int getCameraWidth() {
        return m_camera_width;
    };
    const unsigned int getCameraHeight() {
        return m_camera_height;
    };
    const unsigned int getProjectorWidth() {
        return m_projector_width;
    };
    const unsigned int getProjectorHeight() {
        return m_projector_height;
    };
    const unsigned int getDepthBufferWidth() {
        return m_depth_buffer_width;
    };
    const unsigned int getDepthBufferHeight() {
        return m_depth_buffer_height;
    };
    void setSelectionPoints(const vector<ofVec2f>& points) {
        // store copy of regular points
        m_selection_points = points;
        
        // create vector for OpenCV
        m_selection_points_cv.clear();
        m_selection_points_cv.push_back(Point2f(points[0].x, points[0].y));
        m_selection_points_cv.push_back(Point2f(points[1].x, points[1].y));
        m_selection_points_cv.push_back(Point2f(points[2].x, points[2].y));
        m_selection_points_cv.push_back(Point2f(points[3].x, points[3].y));
    };
    const vector<ofVec2f>& getSelectionPoints() const {
        return m_selection_points;
    };
    const vector<Point2f>& getOpenCvSelectionPoints() const {
        return m_selection_points_cv;
    };
    const vector<Point2f>& getOpenCvOutputPoints() const {
        return m_output_points_cv;
    };
    void setHomographyMatrix(const Mat& matrix) {
        m_homographic_matrix = matrix;
    };
    const Mat& setHomographyMatrix() const {
        return m_homographic_matrix;
    };
};

