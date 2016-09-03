#pragma once

#include "ofMain.h"
#include "AppModel.hpp"
#include "AppEvent.hpp"
#include "UpdateStateCommand.hpp"
#include "ViewManager.hpp"
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
    timelymatter::AppModel& m_app_model;
    // event refernece
    AppEvent& m_app_event;
    // commands
    UpdateStateCommand m_update_state_cmd;
    // views
    ViewManager m_view_manager;
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
