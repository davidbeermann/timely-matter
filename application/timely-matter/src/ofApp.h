#pragma once

#include "ofMain.h"
#include "AppModel.hpp"
#include "ProjectorModel.hpp"
#include "KinectModel.hpp"
#include "AppEvent.hpp"
#include "ViewEvent.hpp"
#include "StartupCommand.hpp"
#include "ResetCommand.hpp"
#include "SaveSettingsCommand.hpp"
#include "UpdateStateCommand.hpp"
#include "UpdateModeCommand.hpp"
#include "UpdateProjectorCalibrationCommand.hpp"
#include "UpdateDepthCalibrationCommand.hpp"
#include "ViewManager.hpp"
#include "GuiView.hpp"

using namespace timelymatter;


class ofApp : public ofBaseApp {
    // model references
    AppModel& m_app_model;
    ProjectorModel& m_projector_model;
    KinectModel& m_kinect_model;
    // event references
    AppEvent& m_app_event;
    ViewEvent& m_view_event;
    // commands
    StartupCommand m_startup_cmd;
    ResetCommand m_reset_cmd;
    UpdateStateCommand m_update_state_cmd;
    SaveSettingsCommand m_save_settings_cmd;
    UpdateModeCommand m_update_mode_cmd;
    UpdateProjectorCalibrationCommand m_update_projector_calibration_cmd;
    UpdateDepthCalibrationCommand m_update_depth_calibration_cmd;
    // views
    ViewManager m_view_manager;
    GuiView m_gui_view;
public:
    ofApp();
    void setup();
    void update();
    void draw();
};

