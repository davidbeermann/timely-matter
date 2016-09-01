#include "KinectRenderView.hpp"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace cv;
using namespace ofxCv;


void KinectRenderView::m_onWindowResized(const int width, const int height) {
    float x = (ofGetWindowWidth() - m_model.getProjectorWidth()) * 0.5f;
    float y = (ofGetWindowHeight() - m_model.getProjectorHeight()) * 0.5f;
    m_center_position.set(x, y);
}


void KinectRenderView::m_doSetup() {
    // set depth clipping
    // the closer the range the better results for the texture gray values between 0-255.
    m_kinect_ptr->setDepthClipping(m_model.getDepthClippingNear(), m_model.getDepthClippingFar());
    
    // allocate buffers
    m_full_depth_image.allocate(m_kinect_ptr->width, m_kinect_ptr->height, OF_IMAGE_GRAYSCALE);
    m_crop_depth_image.allocate(m_model.getDepthBufferWidth(), m_model.getDepthBufferHeight(), OF_IMAGE_GRAYSCALE);
    
    // setup vector field
    m_vector_field.setup(m_model.getProjectorWidth(), m_model.getProjectorHeight(), m_model.getDepthBufferWidth(), m_model.getDepthBufferHeight(), 32);
    
    // setup particle system
    m_particle_system.setup(100, ofVec3f(m_model.getProjectorWidth(), m_model.getProjectorHeight(), 0.f));
    
    m_params.setName("Kinect Rendering");
    
    ofNotifyEvent(m_events.onParametersChanged, this);
}


void KinectRenderView::m_doUpdate() {
    if (m_kinect_ptr->isFrameNew()) {
        // read depth date into buffer
        m_full_depth_image.setFromPixels(m_kinect_ptr->getDepthPixels());
        // extract relevant depth date vis homographic transformation
        Mat matrix = findHomography(Mat(m_model.getOpenCvSelectionPoints()), Mat(m_model.getOpenCvOutputPoints()));
        warpPerspective(m_full_depth_image, m_crop_depth_image, matrix, CV_INTER_LINEAR);
        // update depth image for drawing
        m_crop_depth_image.update();
        
        // update vector field with cropped depth data
        m_vector_field.update(m_crop_depth_image.getPixels());
        
        // apply forces of vector field to particle system...
        m_particle_system.applyVectorField(m_vector_field);
        
        // ...and update all particles within the system.
        m_particle_system.update();
    }
}


void KinectRenderView::m_doDraw() {
    ofPushMatrix();
    ofTranslate(m_center_position);
    
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(m_model.getProjectorSize());
    ofPopStyle();
    
    m_vector_field.draw();
    m_particle_system.draw(m_vector_field);
    
    ofPopMatrix();
}


const ofParameterGroup& KinectRenderView::m_doGetParams() {
    return m_params;
}

