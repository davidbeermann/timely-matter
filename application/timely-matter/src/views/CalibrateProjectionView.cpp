#include "CalibrateProjectionView.hpp"
#include "ParameterUtils.hpp"
#include "BitmapStringUtils.hpp"
#include "ofxOpenCv.h"
#include "ofxCv.h"

#define PADDING 18
#define BITMAP_TEXT_OFFSET_Y 5

using namespace timelymatter;
using namespace ofxCv;
using namespace cv;


void CalibrateProjectionView::m_onSelectionUpdated() {
    vector<ofVec2f> points = m_selection.getPoints();
    m_selection_path.clear();
    m_selection_path.setFilled(true);
    m_selection_path.setFillColor(m_selection_color);
    m_selection_path.moveTo(points[0]);
    m_selection_path.lineTo(points[1]);
    m_selection_path.lineTo(points[2]);
    m_selection_path.lineTo(points[3]);
    m_selection_path.close();
}


void CalibrateProjectionView::m_onWindowResized(const int width, const int height) {
    // calculate position of view title
    m_title_rect.setPosition((ofGetWidth() - m_title_rect.getWidth()) * 0.5f, PADDING + BITMAP_TEXT_LINE_HEIGHT);
    
    // calculate position of confirmation message
    m_confirm_rect.setPosition((ofGetWidth() - m_confirm_rect.getWidth()) * 0.5f, ofGetHeight() - PADDING - m_confirm_rect.getHeight());
    
    // calculate position of selection with infrared image
    m_selection_position.set(PADDING, (ofGetHeight() - m_infrared_buffer.getHeight()) * 0.5f);
    m_selection.updatePosition(m_selection_position);
    
    // calculate position of scaled depth preview
    m_depth_rect.setPosition(width - PADDING - m_depth_rect.getWidth(), m_selection_position.y);
    
    // calculate position for cropped depth output
    m_crop_rect.setPosition(m_depth_rect.getX(), m_depth_rect.getY() + m_depth_rect.getHeight() + PADDING);
    
    // apply loaded settings at first window resize,
    // due to internal absolute positioning of ImageSelection
    //TODO refactor ImageSelection to handle position changes internally
    if (m_kinect_model.settingsLoaded()) {
        m_selection.setHandlePositions(m_kinect_model.getSelectionPoints());
        m_onSelectionUpdated();
    }
}


void CalibrateProjectionView::m_onSetup() {
    // setup selection
    m_selection.setup(m_kinect_sptr->width, m_kinect_sptr->height);
    m_selection.enableMask(false);
    
    m_selection_color.set(255, 0, 0, 255*0.2); // 20% alpha
    
    // add listener to selection updates
    ofAddListener(m_selection.updated, this, &CalibrateProjectionView::m_onSelectionUpdated);
    
    // allocate image buffers
    m_infrared_buffer.allocate(m_kinect_sptr->width, m_kinect_sptr->height, OF_IMAGE_COLOR);
    m_grayscale.allocate(m_kinect_sptr->width, m_kinect_sptr->height);
    m_depth_buffer.allocate(m_kinect_sptr->width, m_kinect_sptr->height, OF_IMAGE_GRAYSCALE);
    m_crop_buffer.allocate(m_kinect_model.getDepthBufferWidth(), m_kinect_model.getDepthBufferHeight(), OF_IMAGE_GRAYSCALE);
    
    // set rectangle sizes to draw scaled buffers
    m_depth_rect.setSize(m_kinect_sptr->width * 0.5, m_kinect_sptr->height * 0.5);
    int h = (m_depth_rect.getWidth() / m_crop_buffer.getWidth()) * m_crop_buffer.getHeight();
    m_crop_rect.setSize(m_depth_rect.getWidth(), h);
    
    // set text rectangles
    m_title_rect = getBitmapStringBoundingBox(m_view_title);
    m_confirm_rect = getBitmapStringBoundingBox(m_confirm_msg);
    
    // define GUI parameters
    GuiUpdateArgs args;
    // infrared params
    ofParameterGroup infrared_params;
    setupInfraredParameters(infrared_params, m_param_norm_min, m_param_norm_max);
    args.params.push_back(infrared_params);
    // depth clipping params
    ofParameterGroup clip_params;
    setupDepthClippingParameters(clip_params, m_param_clip_near, m_param_clip_far);
    args.params.push_back(clip_params);
    
    // send event to update GUI
    ofNotifyEvent(m_view_event.update_gui, args, this);
}


void CalibrateProjectionView::m_onUpdate() {
    m_kinect_sptr->setDepthClipping(m_param_clip_near, m_param_clip_far);
    
    m_kinect_sptr->update();
    
    if (m_kinect_sptr->isFrameNew()) {
        // read infrared pixels data to buffer
        m_infrared_buffer.setFromPixels(m_kinect_sptr->getPixels());
        
        // convert to grayscale image
        m_grayscale = m_infrared_buffer;
        
        // Lighten the grayscale image
        // ---------------------------
        // Solution found here:
        // https://forum.openframeworks.cc/t/levels-with-opencv/1314/6
        // thx @memo
        cvNormalize(m_grayscale.getCvImage(), m_grayscale.getCvImage(), m_param_norm_min, m_param_norm_max, CV_MINMAX, NULL);
        
        // update image within selection container
        m_selection.getImage().setFromPixels(m_grayscale.getPixels());
        
        // update depth pixels
        m_depth_buffer.setFromPixels(m_kinect_sptr->getDepthPixels());
        
        // get input points from selection
        vector<Point2f> input_points = m_selection.getPointsForCv();
        
        // apply homography transformation
        warpPerspective(m_depth_buffer, m_crop_buffer, m_kinect_model.getHomographyMatrix(input_points), CV_INTER_LINEAR);
        
        // update buffers for diplay
        m_depth_buffer.update();
        m_crop_buffer.update();
    }
}


void CalibrateProjectionView::m_onDraw() {
    m_selection.draw();
    m_depth_buffer.draw(m_depth_rect);
    m_crop_buffer.draw(m_crop_rect);
    
    ofPushMatrix();
    ofTranslate(m_title_rect.getTopLeft());
    ofDrawBitmapString(m_view_title, 0, 0);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(m_selection_position);
    ofDrawBitmapString(m_infrared_title, 0, -BITMAP_TEXT_OFFSET_Y);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(m_depth_rect.getTopLeft());
    ofDrawBitmapString(m_buffer_title, 0, -BITMAP_TEXT_OFFSET_Y);
    ofScale(0.5f, 0.5f);
    m_selection_path.draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(m_crop_rect.getTopLeft());
    ofDrawBitmapString(m_extract_title, 0, -BITMAP_TEXT_OFFSET_Y);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(m_confirm_rect.getTopLeft());
    ofDrawBitmapString(m_confirm_msg, 0, 0);
    ofPopMatrix();
}


CalibrateProjectionView::CalibrateProjectionView() : m_kinect_sptr(m_kinect_model.getKinect()) {
    ofRegisterKeyEvents(this);
}


CalibrateProjectionView::~CalibrateProjectionView() {
    ofUnregisterKeyEvents(this);
}


void CalibrateProjectionView::keyPressed(ofKeyEventArgs& args) {
    if (args.key == OF_KEY_RETURN) {
        CalibrateProjectionArgs args;
        args.selection_points = m_selection.getPoints();
        args.depth_clip_near = m_param_clip_near;
        args.depth_clip_far = m_param_clip_far;
        
        ofNotifyEvent(m_view_event.projection_calibrated, args, this);
    }
}

