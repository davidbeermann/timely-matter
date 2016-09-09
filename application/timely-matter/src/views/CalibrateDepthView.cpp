#include "CalibrateDepthView.hpp"
#include "BitmapStringUtils.hpp"
#include "ParameterUtils.hpp"
#include "ViewEvent.hpp"
#include "ofxCv.h"

using namespace timelymatter;
using namespace ofxCv;


void CalibrateDepthView::m_onWindowResized(const int width, const int height) {
    float x = (ofGetWindowWidth() - m_projector_model.getWidth()) * 0.5f;
    float y = (ofGetWindowHeight() - m_projector_model.getHeight()) * 0.5f;
    m_center_position.set(x, y);
}


void CalibrateDepthView::m_onSetup() {
    float fbo_scale = 0.25f;
    m_fbo_output_size.set(0, 0, (int) (m_kinect_sptr->width * fbo_scale), (int) (m_kinect_sptr->height * fbo_scale));
    
    // allocate buffers
    m_selection_fbo.allocate(m_kinect_sptr->width, m_kinect_sptr->height, GL_RGBA, 4);
    m_output_fbo.allocate(m_kinect_sptr->width, m_kinect_sptr->height, GL_RGBA, 4);
    m_kinect_image.allocate(m_kinect_sptr->width, m_kinect_sptr->height, OF_IMAGE_GRAYSCALE);
    m_depth_image.allocate(m_kinect_model.getDepthBufferWidth(), m_kinect_model.getDepthBufferHeight(), OF_IMAGE_GRAYSCALE);
    
    // create path to draw selection overlay
    ofPath path;
    path.setFilled(true);
    path.setFillColor(ofColor(255, 0, 0, 191)); // 75% alpha
    path.moveTo(m_kinect_model.getSelectionPoints()[0]);
    path.lineTo(m_kinect_model.getSelectionPoints()[1]);
    path.lineTo(m_kinect_model.getSelectionPoints()[2]);
    path.lineTo(m_kinect_model.getSelectionPoints()[3]);
    path.close();
    
    // draw selection overlay to fbo
    m_selection_fbo.begin();
    ofClear(0);
    path.draw();
    m_selection_fbo.end();
    
    // setup vector field
    m_vector_field.setup(m_projector_model.getWidth(), m_projector_model.getHeight(), m_kinect_model.getDepthBufferWidth(), m_kinect_model.getDepthBufferHeight(), 32);
    
    // setup gui parameters
    GuiUpdateArgs args;
    // kinect depth params
    ofParameterGroup depth_params;
    args.params.push_back(setupDepthClippingParameters(depth_params, m_param_clip_near, m_param_clip_far));
    // vector field params
    args.params.push_back(m_vector_field.getParams());
    
    // send event to update GUI
    ofNotifyEvent(m_view_event.update_gui, args, this);
}


void CalibrateDepthView::m_onUpdate() {
    // set depth clipping
    // the closer the range the better results for the texture gray values between 0-255.
    m_kinect_sptr->setDepthClipping(m_param_clip_near, m_param_clip_far);
    
    m_kinect_sptr->update();
    
    if (m_kinect_sptr->isFrameNew()) {
        // update output fbo
        m_output_fbo.begin();
        // draw kinect depth output
        m_kinect_sptr->getDepthTexture().draw(0, 0);
        // draw selection overlay
        m_selection_fbo.draw(0, 0);
        m_output_fbo.end();
        
        // read depth date into buffer
        m_kinect_image.setFromPixels(m_kinect_sptr->getDepthPixels());
        // extract relevant depth area via homography transformation
        warpPerspective(m_kinect_image, m_depth_image, m_kinect_model.getHomographyMatrix(), CV_INTER_LINEAR);
        // update depth image for drawing
        m_depth_image.update();
        
        m_vector_field.update(m_depth_image.getPixels());
    }
}


void CalibrateDepthView::m_onDraw() {
    ofPushMatrix();
    ofTranslate(m_center_position);
    
    string avg = "Mark Datum - Current Average: " + to_string(m_vector_field.getAverageDatum()) + " - Ideal Average: 127";
    ofRectangle bounds = getBitmapStringBoundingBox(avg);
    ofDrawBitmapString(avg, (m_projector_model.getWidth() - bounds.getWidth()) * 0.5f, -5.f);
    
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(0, 0, m_projector_model.getWidth(), m_projector_model.getHeight());
    ofPopStyle();
    m_depth_image.draw(m_projector_model.getSize());
    m_vector_field.draw();
    
    ofTranslate(-(m_fbo_output_size.width + 2), 0);
    m_output_fbo.draw(m_fbo_output_size);
    
    ofTranslate(0, m_fbo_output_size.height + 2);
    m_depth_image.draw(m_fbo_output_size);
    
    ofPopMatrix();
}


CalibrateDepthView::CalibrateDepthView() : m_kinect_sptr(m_kinect_model.getKinect()) {
    ofRegisterKeyEvents(this);
}


CalibrateDepthView::~CalibrateDepthView() {
    ofUnregisterKeyEvents(this);
}


void CalibrateDepthView::keyPressed(ofKeyEventArgs& args) {
    if (args.key == OF_KEY_RETURN) {
        CalibrateDepthArgs args;
        args.depth_clip_near = m_param_clip_near;
        args.depth_clip_far = m_param_clip_far;
        args.vector_force_field = m_vector_field.getMaxFieldForce();
        args.vector_force_edge = m_vector_field.getMaxEdgeForce();
        
        ofNotifyEvent(m_view_event.depth_calibrated, args, this);
    }
}

