#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "AppView.hpp"


class KinectView : public AppView {
protected:
    virtual void m_doSetup() = 0;
    virtual void m_doUpdate() = 0;
    virtual void m_doDraw() = 0;
    ofxKinect* m_kinect_ptr = nullptr;
public:
    ~KinectView() {
        if (m_kinect_ptr != nullptr) {
            delete m_kinect_ptr;
            m_kinect_ptr = nullptr;
        }
    };
    
    void setup(ofxKinect* kinect_ptr) {
        m_kinect_ptr = kinect_ptr;
        m_doSetup();
    };
    
    void update() { m_doUpdate(); };
    void draw() { m_doDraw(); };
};