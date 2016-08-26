#include "ofApp.h"

#define INPUT_IMAGE "the-swerve.jpg"
#define OUTPUT_IMAGE "blank-book.jpg"
#define HOMOGRAPHY_INPUT_RECTIFIED "homography-in-rect.yml"
#define HOMOGRAPHY_RECTIFIED_OUTPUT "homography-rect-out.yml"

using namespace ofxCv;
using namespace cv;


void ofApp::calculateTransformations() {
    // calculate homographic transformation matrices
    m_homography_input_rect = findHomography(Mat(m_input.getPoints()), Mat(m_rectified.getPoints()));
    m_homography_rect_output = findHomography(Mat(m_rectified.getPoints()), Mat(m_output.getPoints()));
    
    applyTransformations();
}


void ofApp::saveTransformations() {
    // save homographic transformation matrices to yaml files
    FileStorage fs_in_rect(ofToDataPath(HOMOGRAPHY_INPUT_RECTIFIED), FileStorage::WRITE);
    fs_in_rect << "homography" << m_homography_input_rect;
    
    FileStorage fs_rect_out(ofToDataPath(HOMOGRAPHY_RECTIFIED_OUTPUT), FileStorage::WRITE);
    fs_rect_out << "homography" << m_homography_rect_output;
}


void ofApp::loadTransformations() {
    // load homographic transformation matrices from yaml files
    ofFile yaml_in_rect(HOMOGRAPHY_INPUT_RECTIFIED);
    if(yaml_in_rect.exists()) {
        FileStorage fs(ofToDataPath(HOMOGRAPHY_INPUT_RECTIFIED), FileStorage::READ);
        fs["homography"] >> m_homography_input_rect;
    }
    
    ofFile yaml_rect_out(HOMOGRAPHY_RECTIFIED_OUTPUT);
    if(yaml_rect_out.exists()) {
        FileStorage fs(ofToDataPath(HOMOGRAPHY_RECTIFIED_OUTPUT), FileStorage::READ);
        fs["homography"] >> m_homography_rect_output;
    }
    
    applyTransformations();
}


void ofApp::applyTransformations() {
    // this is how you warp one ofImage into another ofImage given the homography matrix
    // CV INTER NN is 113 fps, CV_INTER_LINEAR is 93 fps
    warpPerspective(m_input.getImage(), m_rectified.getImage(), m_homography_input_rect, CV_INTER_LINEAR);
    // update texture for drawing
    m_rectified.getImage().update();
    
    warpPerspective(m_rectified.getImage(), m_output.getImage(), m_homography_rect_output, CV_INTER_LINEAR);
    
    m_output.getImage().update();
}


void ofApp::setup() {
    float padding = 40.f;
    ofVec2f position = ofVec2f(20, 20);
    
    m_input.setup(position, INPUT_IMAGE);
    
    position.x += m_input.getWidth() + padding;
    m_rectified.setup(position, 210, 297);
    
    position.x += m_rectified.getWidth() + padding;
    m_output.setup(position, OUTPUT_IMAGE);
    m_output.enableMask(true);
    
    m_output_image.load(OUTPUT_IMAGE);
}


void ofApp::draw() {
    m_input.draw();
    m_rectified.draw();
    
    ofPushMatrix();
    ofTranslate(m_output.getPosition());
    m_output_image.draw(0, 0);
    ofPopMatrix();
    
    m_output.draw();
}


void ofApp::keyPressed(int key) {
    switch (key) {
        case 'h':
            calculateTransformations();
            break;
        case 's':
            saveTransformations();
            break;
        case 'l':
            loadTransformations();
            break;
    }
}
