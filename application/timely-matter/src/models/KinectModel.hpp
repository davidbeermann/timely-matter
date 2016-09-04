#pragma once

#include "ofxKinect.h"
#include "ofxOpenCv.h"

using namespace cv;


namespace timelymatter {

    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class KinectModel {
        // private constructor
        KinectModel();
        
        shared_ptr<ofxKinect> m_kinect_sptr;
        float m_depth_clip_near;
        float m_depth_clip_far;
        vector<ofVec2f> m_selection_points;
        vector<Point2f> m_cv_selection_points;
        vector<Point2f> m_cv_output_points;
        
    public:
        // static method to retrieve singleton instance
        static KinectModel& get();
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        KinectModel(KinectModel const&) = delete;
        void operator=(KinectModel const&) = delete;
        
        // public interface methods
        shared_ptr<ofxKinect> getKinect();
        const unsigned int getDepthBufferWidth() const;
        const unsigned int getDepthBufferHeight() const;
        const vector<ofVec2f>& getSelectionPoints() const;
        const vector<Point2f>& getCvSelectionPoints() const;
        const vector<Point2f>& getCvOutputPoints() const;
    };

}