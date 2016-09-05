#include "ofApp.h"
#include "AppState.hpp"

#define PROJECTOR_WIDTH 1024
#define PROJECTOR_HEIGHT 768


ofApp::ofApp() :
    m_app_model(AppModel::get()),
    m_projector_model(ProjectorModel::get()),
    m_kinect_model(KinectModel::get()),
    m_app_event(AppEvent::get()),
    m_view_event(ViewEvent::get())
{}


void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(33);
    
    // configure models
    m_projector_model.setSize(PROJECTOR_WIDTH, PROJECTOR_HEIGHT);
    m_kinect_model.setDepthBufferSize(PROJECTOR_WIDTH * 0.5f, PROJECTOR_HEIGHT * 0.5f);
    
    // setup command mapping
    // app events
    ofAddListener(m_app_event.update_state, &m_update_state_cmd, &UpdateStateCommand::execute);
    // view events
    ofAddListener(m_view_event.mode_selected, &m_update_mode_cmd, &UpdateModeCommand::execute);
    ofAddListener(m_view_event.projection_calibrated, &m_update_projector_calibration_cmd, &UpdateProjectorCalibrationCommand::execute);
    ofAddListener(m_view_event.depth_calibrated, &m_update_depth_calibration_cmd, &UpdateDepthCalibrationCommand::execute);
    
    // setup views
    m_view_manager.setup();
    m_gui_view.setup();
    
    // set initial state
    AppState state = AppState::SELECT_MODE;
    ofNotifyEvent(m_app_event.update_state, state, this);
}


void ofApp::update() {
    m_view_manager.update();
    m_gui_view.update();
}


void ofApp::draw() {
    m_view_manager.draw();
    m_gui_view.draw();
}

