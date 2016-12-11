#pragma once

#include "BaseView.hpp"
#include "ofMain.h"
#include "ofxKinect.h"
#include "VectorField.hpp"

using namespace cv;


namespace timelymatter
{
    class CalibrateDepthView : public BaseView {
        shared_ptr<ofxKinect> m_kinect_sptr;
        
        string m_view_title = "CALIBRATE DEPTH FIELD";
        string m_confirm_msg = "Press <Enter> to confirm selection";
        ofRectangle m_view_title_rect;
        ofRectangle m_confirm_msg_rect;
        
        ofRectangle m_output_rect;
        ofRectangle m_selection_rect;
        ofImage m_kinect_image;
        ofImage m_depth_image;
        ofFbo m_selection_fbo;
        ofFbo m_depth_selection_fbo;
        VectorField m_vector_field;
        string m_info;
        ofRectangle m_info_rect;
        
        ofParameter<bool> m_param_show_selection;
        ofParameter<bool> m_param_show_depth;
        ofParameter<unsigned int> m_param_clip_near;
        ofParameter<unsigned int> m_param_clip_far;
        
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
    public:
        CalibrateDepthView();
        ~CalibrateDepthView();
        // key event listener methods
        void keyPressed(ofKeyEventArgs& args);
        void keyReleased(ofKeyEventArgs& args) {};
    };
}