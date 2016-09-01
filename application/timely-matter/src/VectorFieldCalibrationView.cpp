#include "VectorFieldCalibrationView.hpp"
#include "Utils.hpp"
#include "ofEvents.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace cv;
using namespace ofxCv;
using namespace timelymatter;


void VectorFieldCalibrationView::m_onWindowResized(const int width, const int height) {
    float x = (ofGetWindowWidth() - m_model.getProjectorWidth()) * 0.5f;
    float y = (ofGetWindowHeight() - m_model.getProjectorHeight()) * 0.5f;
    m_center_position.set(x, y);
}


void VectorFieldCalibrationView::m_doSetup() {
    float fbo_scale = 0.25f;
    m_fbo_output_size.set(0, 0, (int) (m_kinect_ptr->width * fbo_scale), (int) (m_kinect_ptr->height * fbo_scale));
    
    // allocate buffers
    m_selection_fbo.allocate(m_kinect_ptr->width, m_kinect_ptr->height, GL_RGBA, 4);
    m_output_fbo.allocate(m_kinect_ptr->width, m_kinect_ptr->height, GL_RGBA, 4);
    m_kinect_image.allocate(m_kinect_ptr->width, m_kinect_ptr->height, OF_IMAGE_GRAYSCALE);
    m_depth_image.allocate(m_model.getDepthBufferWidth(), m_model.getDepthBufferHeight(), OF_IMAGE_GRAYSCALE);
    
    // create path to draw selection overlay
    ofPath path;
    path.setFilled(true);
    path.setFillColor(ofColor(255, 0, 0, 191)); // 75% alpha
    path.moveTo(m_model.getSelectionPoints()[0]);
    path.lineTo(m_model.getSelectionPoints()[1]);
    path.lineTo(m_model.getSelectionPoints()[2]);
    path.lineTo(m_model.getSelectionPoints()[3]);
    path.close();
    
    // draw selection overlay to fbo
    m_selection_fbo.begin();
    ofClear(0);
    path.draw();
    m_selection_fbo.end();
    
    // setup vector field
    m_vector_field.setup(m_model.getProjectorWidth(), m_model.getProjectorHeight(), m_model.getDepthBufferWidth(), m_model.getDepthBufferHeight(), 32);
    
    // setup gui parameters
    m_params.setName("Vector Field Calibration");
    // kinect depth params
    ofParameterGroup depth_params;
    depth_params.setName("Kinect Depth FoV");
    depth_params.add(m_param_depth_near.set("Near plane", 1000, 500, 2500));
    depth_params.add(m_param_depth_far.set("Far plane", 2500, 500, 4000));
    m_params.add(depth_params);
    // vector field params
    m_params.add(m_vector_field.getGuiParams());
    
    // notify gui about update
    ofNotifyEvent(m_events.onParametersChanged, this);
}


void VectorFieldCalibrationView::m_doUpdate() {
    // set depth clipping
    // the closer the range the better results for the texture gray values between 0-255.
    m_kinect_ptr->setDepthClipping(m_param_depth_near, m_param_depth_far);
    
    if (m_kinect_ptr->isFrameNew()) {
        // update output fbo
        m_output_fbo.begin();
        // draw kinect depth output
        m_kinect_ptr->getDepthTexture().draw(0, 0);
        // draw selection overlay
        m_selection_fbo.draw(0, 0);
        m_output_fbo.end();
        
        // read depth date into buffer
        m_kinect_image.setFromPixels(m_kinect_ptr->getDepthPixels());
        // extract relevant depth date vis homographic transformation
        Mat matrix = findHomography(Mat(m_model.getOpenCvSelectionPoints()), Mat(m_model.getOpenCvOutputPoints()));
        warpPerspective(m_kinect_image, m_depth_image, matrix, CV_INTER_LINEAR);
        // update depth image for drawing
        m_depth_image.update();
        
        m_vector_field.update(m_depth_image.getPixels());
    }
}


void VectorFieldCalibrationView::m_doDraw() {
    ofPushMatrix();
    ofTranslate(m_center_position);
    
    string avg = "Mark Datum - Current Average: " + to_string(m_vector_field.getAverageDatum()) + " - Ideal Average: 127";
    ofRectangle bounds = getBitmapStringBoundingBox(avg);
    ofDrawBitmapString(avg, (m_model.getProjectorWidth() - bounds.getWidth()) * 0.5f, -5.f);
    
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(0, 0, m_model.getProjectorWidth(), m_model.getProjectorHeight());
    ofPopStyle();
    m_depth_image.draw(m_model.getProjectorSize());
    m_vector_field.draw();
    
    ofTranslate(-(m_fbo_output_size.width + 2), 0);
    m_output_fbo.draw(m_fbo_output_size);
    
    ofTranslate(0, m_fbo_output_size.height + 2);
    m_depth_image.draw(m_fbo_output_size);
    
    ofPopMatrix();
}


const ofParameterGroup& VectorFieldCalibrationView::m_doGetParams() {
    return m_params;
}

