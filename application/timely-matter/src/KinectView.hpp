#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "AppView.hpp"


class KinectView : public AppView {
protected:
    virtual void m_doSetup() = 0;
    virtual void m_doUpdate() = 0;
    virtual void m_doDraw() = 0;
    virtual const ofParameterGroup& m_doGetParams() = 0;
    ofxKinect* m_kinect_ptr = nullptr;
    
public:
    virtual ~KinectView(){
        // do not delete pointer, since it is managed by KinectInputProvider
        m_kinect_ptr = nullptr;
    };
    
    void setup(ofxKinect* kinect_sptr) {
        m_kinect_ptr = kinect_sptr;
        
        m_onWindowResized(ofGetWindowWidth(), ofGetWindowHeight());
        
        m_doSetup();
    };
    
    void update() { m_doUpdate(); };
    void draw() { m_doDraw(); };
    const ofParameterGroup& getParams() { return m_doGetParams(); };
};