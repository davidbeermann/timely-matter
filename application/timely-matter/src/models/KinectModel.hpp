#pragma once

#include "ofxKinect.h"


namespace timelymatter {

    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class KinectModel {
        // private constructor
        KinectModel();
        
        ofxKinect m_kinect;
        float m_depth_clip_near;
        float m_depth_clip_far;
        
    public:
        // static method to retrieve singleton instance
        static KinectModel& get();
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        KinectModel(KinectModel const&) = delete;
        void operator=(KinectModel const&) = delete;
        
        // public interface methods
        ofxKinect& getKinect();
    };

}