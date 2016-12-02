#include "ofApp.h"
#include "AppState.hpp"
#include "AppConfig.hpp"

#define PROJECTOR_WIDTH 1920 // 1024 1280 1920 960
#define PROJECTOR_HEIGHT 1080 // 768 800 1080 540


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
    
    AppConfig& c = AppConfig::get();
    if (!c.load()) {
        ofLogError() << "Configuration file could not be loaded!";
    } else {
        ofLog() << "Configuration file sucessfully loaded.";
        ofLog() << "- - - - - - - - - - - - - - - - - - - -";
        ofLog() << "Kinect Crop Ratio: " << c.getKinectCropRatio();
        ofLog() << "Projector Width: " << c.getProjectorWidth();
        ofLog() << "Projector Height: " << c.getProjectorHeight();
        ofLog() << "Projector Render Ratio: " << c.getProjectorRenderRatio();
        ofLog() << "Projector Render Width: " << c.getProjectorRenderWidth();
        ofLog() << "Projector Render Height: " << c.getProjectorRenderHeight();
        ofLog() << "Particle System Count: " << c.getParticleSystemCount();
        ofLog() << "Particle System Min Radius: " << c.getParticleSystemMinRadius();
        ofLog() << "Particle System Max Radius: " << c.getParticleSystemMaxRadius();
        ofLog() << "Marching Squares Columns: " << c.getMarchingSquaresColumns();
        ofLog() << "Marching Squares Rows: " << c.getMarchingSquaresRows();
        ofLog() << "- - - - - - - - - - - - - - - - - - - -";
    }
    
    // configure models
    m_projector_model.setSize(PROJECTOR_WIDTH, PROJECTOR_HEIGHT);
    m_kinect_model.setDepthBufferSize(PROJECTOR_WIDTH * 0.5f, PROJECTOR_HEIGHT * 0.5f);
    
    // setup command mapping
    // app events
    ofAddListener(m_app_event.startup, &m_startup_cmd, &StartupCommand::execute);
    ofAddListener(m_app_event.reset, &m_reset_cmd, &ResetCommand::execute);
    ofAddListener(m_app_event.update_state, &m_update_state_cmd, &UpdateStateCommand::execute);
    ofAddListener(m_app_event.save_settings, &m_save_settings_cmd, &SaveSettingsCommand::execute);
    ofAddListener(m_app_event.load_settings, &m_load_settings_cmd, &LoadSettingsCommand::execute);
    // view events
    ofAddListener(m_view_event.mode_selected, &m_update_mode_cmd, &UpdateModeCommand::execute);
    ofAddListener(m_view_event.projection_calibrated, &m_update_projector_calibration_cmd, &UpdateProjectorCalibrationCommand::execute);
    ofAddListener(m_view_event.depth_calibrated, &m_update_depth_calibration_cmd, &UpdateDepthCalibrationCommand::execute);
    
    // setup views
    m_view_manager.setup();
    m_gui_view.setup();
    
    // startup application
    ofNotifyEvent(m_app_event.startup, this);
}


void ofApp::update() {
    m_view_manager.update();
    m_gui_view.update();
}


void ofApp::draw() {
    m_view_manager.draw();
    m_gui_view.draw();
}

