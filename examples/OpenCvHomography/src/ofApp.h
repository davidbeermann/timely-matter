#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ImageSelection.hpp"


class ofApp : public ofBaseApp {
    void m_calculateTransformations();
    void m_saveTransformations();
    void m_loadTransformations();
    void m_applyTransformations();
    ImageSelection m_input;
    ImageSelection m_rectified;
    ImageSelection m_output;
    ofImage m_output_image;
    cv::Mat m_homography_input_rect;
    cv::Mat m_homography_rect_output;
    string m_instructions;
    string m_label_input;
    string m_label_rectified;
    string m_label_output;
public:
    void setup();
    void draw();
    void keyPressed(int key);
};
