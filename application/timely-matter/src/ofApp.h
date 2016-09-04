#pragma once

#include "ofMain.h"
#include "AppModel.hpp"
#include "AppEvent.hpp"
#include "ViewEvent.hpp"
#include "UpdateStateCommand.hpp"
#include "UpdateModeCommand.hpp"
#include "UpdateProjectorCalibrationCommand.hpp"
#include "ViewManager.hpp"
#include "GuiView.hpp"
//#include "ofEvents.h"
//#include "AppUI.hpp"
//#include "AppVars.hpp"
//#include "VectorFieldInputFactory.h"
//#include "VectorFieldInputProvider.h"
//#include "VectorField.h"
//#include "ParticleSystem.h"

using namespace timelymatter;


class ofApp : public ofBaseApp {
    // model references
    AppModel& m_app_model;
    // event references
    AppEvent& m_app_event;
    ViewEvent& m_view_event;
    // commands
    UpdateStateCommand m_update_state_cmd;
    UpdateModeCommand m_update_mode_cmd;
    UpdateProjectorCalibrationCommand m_update_projector_calibration_cmd;
    // views
    ViewManager m_view_manager;
    GuiView m_gui_view;
public:
    ofApp();
    void setup();
    void update();
    void draw();
};


//class ofApp : public ofBaseApp {
//    void m_prepare_for_rendering();
//    
//    AppUI m_ui;
//    VectorFieldInputFactory m_input_factory;
//    VectorFieldInputProvider* m_input_provider;
//    VectorField m_vector_field;
//    ParticleSystem m_particle_system;
//    bool m_is_prepared;
//    
//    ofVec2f mCenteredPos;
//public:
//    void setup();
//    void update();
//    void draw();
//    void windowResized(int w, int h);
//    
//    void updateGuiParameters();
//    
//    const bool isInputAvailable();
//    void setInputProvider(AppMode& mode);
//};
