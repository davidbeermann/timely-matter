#include "CalibrateDepthView.hpp"
#include "BitmapStringUtils.hpp"
#include "ParameterUtils.hpp"
#include "ViewEvent.hpp"
#include "ofxCv.h"
#include "AppConfig.hpp"

#define PADDING 18
#define BOX_MARGIN 4

using namespace timelymatter;
using namespace ofxCv;


void CalibrateDepthView::m_onWindowResized(const int width, const int height) {
    
    // calculate positon of output area
    m_output_rect.setPosition((ofGetWidth() - m_output_rect.getWidth()) * 0.5f, (ofGetHeight() - m_output_rect.getHeight()) * 0.5f);
    
    // calculate position for centered texts
    m_view_title_rect.setPosition((ofGetWidth() - m_view_title_rect.getWidth()) * 0.5f, PADDING + BITMAP_TEXT_LINE_HEIGHT);
    m_confirm_msg_rect.setPosition((ofGetWidth() - m_confirm_msg_rect.getWidth()) * 0.5f, ofGetHeight() - PADDING);
    
}


void CalibrateDepthView::m_onSetup() {
    
    // setup iamge to extract depth data from kinect
    m_kinect_image.allocate(m_kinect_sptr->width, m_kinect_sptr->height, OF_IMAGE_GRAYSCALE);
    m_depth_image.allocate(m_kinect_model.getCropBufferWidth(), m_kinect_model.getCropBufferHeight(), OF_IMAGE_GRAYSCALE);
    
    // setup rect of output area
    m_output_rect.setSize(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight());
    
    // set text rectangles
    m_view_title_rect = getBitmapStringBoundingBox(m_view_title);
    m_confirm_msg_rect = getBitmapStringBoundingBox(m_confirm_msg);
    
    // allocate buffers for selection
    m_selection_fbo.allocate(m_kinect_sptr->width, m_kinect_sptr->height, GL_RGBA, 4);
    m_depth_selection_fbo.allocate(m_kinect_sptr->width, m_kinect_sptr->height, GL_RGBA, 4);
    
    // create path to draw selection overlay
    float alpha = 0.75f; // 75% alpha
    ofPath path;
    path.setFilled(true);
    path.setFillColor(ofColor(255, 0, 0, 255*alpha));
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
    
    // set rectangle for selection
    m_selection_rect.setSize(m_depth_selection_fbo.getWidth(), m_depth_selection_fbo.getHeight());
    m_selection_rect.scale(0.25f);
    m_selection_rect.setPosition(0, m_output_rect.getHeight() - m_selection_rect.getHeight());
    
    // setup vector field
    m_vector_field.setup(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), m_kinect_model.getCropBufferWidth(), m_kinect_model.getCropBufferHeight(), AppConfig::get().getVectorFieldSubdivisionX(), AppConfig::get().getVectorFieldSubdivisionY());
    
    // setup gui parameters
    GuiUpdateArgs args;
    // view params
    ofParameterGroup view_params;
    view_params.setName("Calibrate Depth View");
    view_params.add(m_param_show_selection.set("show selection output", false));
    view_params.add(m_param_show_depth.set("show depth output", false));
    args.params.push_back(view_params);
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
        m_depth_selection_fbo.begin();
        // draw kinect depth output
        m_kinect_sptr->getDepthTexture().draw(0, 0);
        // draw selection overlay
        m_selection_fbo.draw(0, 0);
        m_depth_selection_fbo.end();
        
        // read depth date into buffer
        m_kinect_image.setFromPixels(m_kinect_sptr->getDepthPixels());
        // extract relevant depth area via homography transformation
        warpPerspective(m_kinect_image, m_depth_image, m_kinect_model.getHomographyMatrix(), CV_INTER_LINEAR);
        // update depth image for drawing
        m_depth_image.update();
        
        m_vector_field.update(m_depth_image.getPixels());
    }
    
    m_info = "Average Datum: " + to_string(m_vector_field.getAverageDatum());
    m_info += " - Far Distance: " + to_string((float) m_param_clip_far / 1000.f) + "m";
    m_info += " - Sensitivity Range: " + to_string((float)(m_param_clip_far - m_param_clip_near) / 1000.f) + "m";
    
    m_info_rect = getBitmapStringBoundingBox(m_info);
}


void CalibrateDepthView::m_onDraw() {
    
    ofPushMatrix();
    ofTranslate(m_output_rect.getTopLeft());
    
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(0, 0, m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight());
    ofPopStyle();
    if (m_param_show_depth) {
        m_depth_image.draw(m_projector_model.getBufferSize());
    }
    m_vector_field.draw();
    
    if (m_param_show_selection) {
        m_depth_selection_fbo.draw(m_selection_rect);
    }
    
    ofDrawBitmapString(m_info, (m_projector_model.getBufferWidth() - m_info_rect.getWidth()) * 0.5f, -BOX_MARGIN);
    
    ofPopMatrix();
    
    // draw centered texts
    ofDrawBitmapString(m_view_title, m_view_title_rect.getTopLeft());
    ofDrawBitmapString(m_confirm_msg, m_confirm_msg_rect.getTopLeft());
    
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
    else if (args.key == OF_KEY_TAB) {
        m_param_show_selection = !m_param_show_selection;
    }
    else if (args.key == ' ') {
        m_param_show_depth = !m_param_show_depth;
    }
}

