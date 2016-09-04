#pragma once

#include "ofMain.h"
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
        unsigned int m_depth_clip_near;
        unsigned int m_depth_clip_near_min;
        unsigned int m_depth_clip_near_max;
        unsigned int m_depth_clip_far;
        unsigned int m_depth_clip_far_min;
        unsigned int m_depth_clip_far_max;
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
        
        void setDepthClipNear(const unsigned int& value);
        const unsigned int getDepthClipNear() const {
            return m_depth_clip_near;
        }
        const unsigned int getDepthClipNearMin() const {
            return m_depth_clip_near_min;
        }
        const unsigned int getDepthClipNearMax() const {
            return m_depth_clip_near_max;
        }
        
        void setDepthClipFar(const unsigned int& value);
        const unsigned int getDepthClipFar() const {
            return m_depth_clip_far;
        }
        const unsigned int getDepthClipFarMin() const {
            return m_depth_clip_far_min;
        }
        const unsigned int getDepthClipFarMax() const {
            return m_depth_clip_far_max;
        }
        
        const unsigned int getDepthBufferWidth() const;
        const unsigned int getDepthBufferHeight() const;
        
        const vector<ofVec2f>& getSelectionPoints() const;
        void setSelectionPoints(const vector<ofVec2f>& points);
        const vector<Point2f>& getCvSelectionPoints() const;
        const vector<Point2f>& getCvOutputPoints() const;
    };

}