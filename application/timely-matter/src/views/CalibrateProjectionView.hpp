#pragma once

#include "BaseView.hpp"
#include "ofMain.h"
#include "ofxKinect.h"
#include "ImageSelection.hpp"


namespace timelymatter
{
    class CalibrateProjectionView : public BaseView {
        void m_onSelectionUpdated();
        
        shared_ptr<ofxKinect> m_kinect_sptr;
        string m_infrared_title = "Infrared camera";
        string m_buffer_title = "Depth buffer";
        string m_extract_title = "Depth buffer extract via homography transformation";
        string m_confirm_msg = "Press <Enter> to confirm selection";
        ofVec2f m_selection_position;
        ofVec2f m_depth_position;
        ofVec2f m_crop_position;
        ImageSelection m_selection;
        ofImage m_infrared_buffer;
        ofImage m_depth_buffer;
        ofImage m_crop_buffer;
        ofxCvGrayscaleImage m_grayscale;
        ofPath m_selection_path;
        ofColor m_selection_color;
        ofParameter<float> m_param_norm_min;
        ofParameter<float> m_param_norm_max;
        ofParameter<unsigned int> m_param_clip_near;
        ofParameter<unsigned int> m_param_clip_far;
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
    public:
        CalibrateProjectionView();
        ~CalibrateProjectionView();
        // key event listener methods
        void keyPressed(ofKeyEventArgs& args);
        void keyReleased(ofKeyEventArgs& args) {};
    };
}