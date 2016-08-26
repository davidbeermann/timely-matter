#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ImageSelection.hpp"


class ofApp : public ofBaseApp {
    void calculateTransformations();
    void saveTransformations();
    void loadTransformations();
    void applyTransformations();
    ImageSelection m_input;
    ImageSelection m_rectified;
    ImageSelection m_output;
    ofImage m_output_image;
    cv::Mat m_homography_input_rect;
    cv::Mat m_homography_rect_output;
    
public:
    void setup();
//    void update();
    void draw();
    // event listener
    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
};
