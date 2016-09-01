#pragma once

#include "ofEvents.h"
#include "ofxOpenCv.h"
#include "KinectView.hpp"
#include "ImageSelection.hpp"


class KinectCalibrationView : public KinectView {
    ofVec2f m_selection_position;
    ofVec2f m_depth_position;
    ofVec2f m_crop_position;
    ImageSelection m_selection;
    ofImage m_infrared_buffer;
    ofImage m_depth_buffer;
    ofImage m_crop_buffer;
    ofxCvGrayscaleImage m_grayscale;
    cv::Mat m_homographic_matrix;
    ofParameterGroup m_params;
    ofParameter<float> m_param_norm_min;
    ofParameter<float> m_param_norm_max;
protected:
    void m_onWindowResized(const int width, const int height);
    void m_doSetup();
    void m_doUpdate();
    void m_doDraw();
    const ofParameterGroup& m_doGetParams();
public:
    KinectCalibrationView() {
        ofRegisterKeyEvents(this);
    };
    ~KinectCalibrationView() {
        ofUnregisterKeyEvents(this);
    };
    // key events
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args){};
    // getter
    vector<ofVec2f> getSelectionPoints();
    const cv::Mat& getHomographyMatrix() const;
};