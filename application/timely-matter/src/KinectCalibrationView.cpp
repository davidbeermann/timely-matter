#include "KinectCalibrationView.hpp"
#include "AppVars.hpp"
#include "AppModel.hpp"
#include "ViewEvents.hpp"
#include "ofxCv.h"

#define PADDING 18

using namespace ofxCv;
using namespace cv;


void KinectCalibrationView::keyPressed(ofKeyEventArgs& args) {
    if (args.key == OF_KEY_RETURN) {
        ofNotifyEvent(ViewEvents::get().onKinectCalibrated, this);
    }
}


vector<ofVec2f> KinectCalibrationView::getSelectionPoints() {
    return m_selection.getPoints();
}


const cv::Mat& KinectCalibrationView::getHomographyMatrix() const {
    return m_homographic_matrix;
}


void KinectCalibrationView::m_onWindowResized(const int width, const int height) {
    m_selection_position.set(PADDING, PADDING);
    m_selection.updatePosition(m_selection_position);
    
    m_depth_position.set(PADDING, height - PADDING - m_depth_buffer.getHeight());
    
    float crop_x = width - PADDING - m_kinect_ptr->width + (m_kinect_ptr->width - m_crop_buffer.getWidth()) * 0.5f;
    float crop_y = PADDING + (m_kinect_ptr->height - m_crop_buffer.getHeight()) * 0.5f;
    m_crop_position.set(crop_x, crop_y);
}


void KinectCalibrationView::m_doSetup() {
    // setup selection
    m_selection.setup(m_kinect_ptr->width, m_kinect_ptr->height);
    m_selection.enableMask(false);
    
    // allocate image buffers
    m_infrared_buffer.allocate(m_kinect_ptr->width, m_kinect_ptr->height, OF_IMAGE_COLOR);
    m_grayscale.allocate(m_kinect_ptr->width, m_kinect_ptr->height);
    m_depth_buffer.allocate(m_kinect_ptr->width, m_kinect_ptr->height, OF_IMAGE_GRAYSCALE);
    m_crop_buffer.allocate(AppModel::get().getDepthBufferWidth(), AppModel::get().getDepthBufferHeight(), OF_IMAGE_GRAYSCALE);
    
    
    // define GUI parameters
    m_params.setName("Depth Crop Configuration");
    // infrared params
    ofParameterGroup infrared_params;
    infrared_params.setName("Infrared Normalization");
    infrared_params.add(m_param_norm_min.set("Min", 33.f, 0.f, 255.f));
    infrared_params.add(m_param_norm_max.set("Max", 255.f, 0.f, 255.f));
    m_params.add(infrared_params);
    
    // send event to update GUI
    ofNotifyEvent(ViewEvents::get().onParametersChanged, this);
}


void KinectCalibrationView::m_doUpdate() {
    // read infrared pixels data to buffer
    m_infrared_buffer.setFromPixels(m_kinect_ptr->getPixels());
    
    // convert to grayscale image
    m_grayscale = m_infrared_buffer;
    
    // Lighten the grayscale image
    // ---------------------------
    // Solution found here:
    // https://forum.openframeworks.cc/t/levels-with-opencv/1314/6
    cvNormalize(m_grayscale.getCvImage(), m_grayscale.getCvImage(), m_param_norm_min, m_param_norm_max, CV_MINMAX, NULL);
    
    // update image within selection container
    m_selection.getImage().setFromPixels(m_grayscale.getPixels());
    
    // update depth pixels
    m_depth_buffer.setFromPixels(m_kinect_ptr->getDepthPixels());
    
    // get input points fon selection
    vector<Point2f> input_points = m_selection.getPointsForCv();
    
    // fixed output frame a quarter size of the final rendering
    vector<Point2f> output_points;
    output_points.push_back(Point2f(0.f, 0.f));
    output_points.push_back(Point2f(m_crop_buffer.getWidth(), 0.f));
    output_points.push_back(Point2f(m_crop_buffer.getWidth(), m_crop_buffer.getHeight()));
    output_points.push_back(Point2f(0.f, m_crop_buffer.getHeight()));
    
    m_homographic_matrix = findHomography(Mat(input_points), Mat(output_points));
    
    // apply homographic transformation
    warpPerspective(m_depth_buffer, m_crop_buffer, m_homographic_matrix, CV_INTER_LINEAR);
    
    // update buffers for diplay
    m_depth_buffer.update();
    m_crop_buffer.update();
}


void KinectCalibrationView::m_doDraw() {
    m_selection.draw();
    
//    ofPushMatrix();
//    ofTranslate(m_depth_position);
    m_depth_buffer.draw(m_depth_position);
//    ofPopMatrix();
    
//    ofPushMatrix();
//    ofTranslate(m_crop_position);
    m_crop_buffer.draw(m_crop_position);
//    ofPopMatrix();
    
}


const ofParameterGroup& KinectCalibrationView::m_doGetParams() {
    return m_params;
}
