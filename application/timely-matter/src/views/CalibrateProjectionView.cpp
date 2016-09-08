#include "CalibrateProjectionView.hpp"
#include "ParameterUtils.hpp"
#include "ofxCv.h"

#define PADDING 18

using namespace timelymatter;
using namespace ofxCv;


void CalibrateProjectionView::m_onWindowResized(const int width, const int height) {
    m_selection_position.set(PADDING, PADDING);
    m_selection.updatePosition(m_selection_position);
    
    m_depth_position.set(PADDING, height - PADDING - m_depth_buffer.getHeight());
    
    float crop_x = width - PADDING - m_kinect_sptr->width + (m_kinect_sptr->width - m_crop_buffer.getWidth()) * 0.5f;
    float crop_y = PADDING + (m_kinect_sptr->height - m_crop_buffer.getHeight()) * 0.5f;
    m_crop_position.set(crop_x, crop_y);
    
    // apply loaded settings at first window resize,
    // due to internal absolute positioning of ImageSelection
    //TODO refactor ImageSelection to handle position changes internally
    if (m_kinect_model.settingsLoaded()) {
        m_selection.setHandlePositions(m_kinect_model.getSelectionPoints());
    }
}


void CalibrateProjectionView::m_onSetup() {
    // setup selection
    m_selection.setup(m_kinect_sptr->width, m_kinect_sptr->height);
    m_selection.enableMask(false);
    
    // allocate image buffers
    m_infrared_buffer.allocate(m_kinect_sptr->width, m_kinect_sptr->height, OF_IMAGE_COLOR);
    m_grayscale.allocate(m_kinect_sptr->width, m_kinect_sptr->height);
    m_depth_buffer.allocate(m_kinect_sptr->width, m_kinect_sptr->height, OF_IMAGE_GRAYSCALE);
    m_crop_buffer.allocate(m_kinect_model.getDepthBufferWidth(), m_kinect_model.getDepthBufferHeight(), OF_IMAGE_GRAYSCALE);
    
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
}


void CalibrateProjectionView::m_onDraw() {
    m_selection.draw();
    m_depth_buffer.draw(m_depth_position);
    m_crop_buffer.draw(m_crop_position);
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

