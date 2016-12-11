#include "ofApp.h"
#include "AppState.hpp"
#include "AppConfig.hpp"


ofApp::ofApp() :
    m_app_model(AppModel::get()),
    m_projector_model(ProjectorModel::get()),
    m_kinect_model(KinectModel::get()),
    m_app_event(AppEvent::get()),
    m_view_event(ViewEvent::get())
{}


void ofApp::setup() {
    AppConfig& config = AppConfig::get();
    if (!config.load()) {
        ofLogError() << "Configuration file could not be loaded!";
    } else {
        
        ofSetFrameRate(60);
        ofSetBackgroundColor(AppConfig::get().getBackgroundColor());
        ofEnableAlphaBlending();
        
        ofLog() << "Configuration file sucessfully loaded.";
        ofLog() << "- - - - - - - - - - - - - - - - - - - -";
        ofLog() << "Output Projector Width: " << config.getOutputProjectorWidth();
        ofLog() << "Output Projector Height: " << config.getOutputProjectorHeight();
        ofLog() << "Output Buffer Width: " << config.getOutputBufferWidth();
        ofLog() << "Output Buffer Height: " << config.getOutputBufferHeight();
        
        ofLog() << "Kinect Crop Buffer Width: " << config.getKinectCropBufferWidth();
        ofLog() << "Kinect Crop Buffer Height: " << config.getKinectCropBufferHeight();
        
        ofLog() << "Vector Field Subdivision X: " << config.getVectorFieldSubdivisionX();
        ofLog() << "Vector Field Subdivision Y: " << config.getVectorFieldSubdivisionY();
        
        ofLog() << "Particle System Count: " << config.getParticleSystemCount();
        ofLog() << "Particle System Min Radius: " << config.getParticleSystemMinRadius();
        ofLog() << "Particle System Max Radius: " << config.getParticleSystemMaxRadius();
        
        ofLog() << "Marching Squares Columns: " << config.getMarchingSquaresColumns();
        ofLog() << "Marching Squares Rows: " << config.getMarchingSquaresRows();
        ofLog() << "- - - - - - - - - - - - - - - - - - - -";
        
        // configure models
        m_projector_model.setSize(config.getOutputProjectorWidth(), config.getOutputProjectorHeight(), config.getOutputBufferWidth(), config.getOutputBufferHeight());
        // THIS METHOD CALL IS MANDATORY!!!!
        m_kinect_model.setCropBufferSize(config.getKinectCropBufferWidth(), config.getKinectCropBufferHeight());
        
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
}


void ofApp::update() {
    if (AppConfig::get().isLoaded()) {
        m_view_manager.update();
        m_gui_view.update();
    }
}


void ofApp::draw() {
    if (AppConfig::get().isLoaded()) {
        m_view_manager.draw();
        m_gui_view.draw();
    }
}

