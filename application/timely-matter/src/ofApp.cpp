#include "ofApp.h"
#include "AppState.hpp"
//#include "ViewEvents.hpp"

//using namespace timelymatter;


ofApp::ofApp() :
m_app_model(timelymatter::AppModel::get()),
m_app_event(AppEvent::get()),
m_view_event(ViewEvent::get()) {
}


void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(33);
    
    // setup command mapping
    // app events
    ofAddListener(m_app_event.update_state, &m_update_state_cmd, &UpdateStateCommand::execute);
    // view events
    ofAddListener(m_view_event.mode_selected, &m_update_mode_cmd, &UpdateModeCommand::execute);
    ofAddListener(m_view_event.projection_calibrated, &m_update_projector_calibration_cmd, &UpdateProjectorCalibrationCommand::execute);
    
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


//void ofApp::setup() {
//    ofSetFrameRate(60);
//    ofSetBackgroundColor(33);
//    
//    m_ui.setup();
//    ofAddListener(m_ui.eventModeSelected, this, &ofApp::setInputProvider);
//    
//    ofAddListener(ViewEvents::get().onParametersChanged, this, &ofApp::updateGuiParameters);
//    
//    m_input_provider = nullptr;
//    m_is_prepared = false;
//}
//
//
//void ofApp::update() {
//    
//    if (isInputAvailable()) {
//        // update input provider first ...
//        m_input_provider->update();
//        
//        if (m_input_provider->isReady()) {
//            if (!m_is_prepared) {
//                m_prepare_for_rendering();
//                m_is_prepared = true;
//            }
//            
//            // ... before retrieving pixel data to update vector field.
//            m_vector_field.update(m_input_provider->getPixels());
//            
//            // apply forces of vector field to particl system...
//            m_particle_system.applyVectorField(m_vector_field);
//            
//            // ...and update all particles within the system.
//            m_particle_system.update();
//        }
//    }
//    
//    m_ui.update();
//}
//
//
//void ofApp::draw() {
//    if (isInputAvailable()) {
//        ofPushMatrix();
////        ofTranslate(mCenteredPos);
//        
////        ofPushStyle();
////        ofSetColor(0);
////        ofDrawRectangle(0, 0, m_input_provider->getWidth(), m_input_provider->getHeight());
////        ofPopStyle();
//        
//        m_input_provider->draw();
//        
//        if (m_is_prepared) {
//            m_vector_field.draw();
//            m_particle_system.draw(m_vector_field);
//        }
//        
//        ofPopMatrix();
//    }
//    
//    m_ui.draw();
//}
//
//
//void ofApp::windowResized(int w, int h) {
//    mCenteredPos.set((w - m_input_provider->getWidth()) * 0.5f, (h - m_input_provider->getHeight()) * 0.5f);
//}
//
//
//void ofApp::updateGuiParameters() {
//    ofLog() << "ofApp::updateGuiParameters()";
//    m_ui.clearParameters();
//    
//    m_input_provider->addParams(m_ui);
//    
//    m_ui.loadSettings();
//}
//
//
//void ofApp::setInputProvider(AppMode& mode) {
//    // clear prior input
//    if (isInputAvailable()) {
//        delete m_input_provider;
//        m_input_provider = nullptr;
//        //TODO reset vector field and particle system
//        m_ui.clearParameters();
//    }
//    
//    // setup input provider
//    m_input_provider = m_input_factory.get(mode);
//    m_input_provider->setup();
//    
//    ofLog() << "input setup complete: " << m_input_provider->getName();
//    
//    // update window positions
//    windowResized(ofGetWindowWidth(), ofGetWindowHeight());
//}
//
//
//const bool ofApp::isInputAvailable() {
//    return m_input_provider != nullptr;
//}
//
//
//void ofApp::m_prepare_for_rendering() {
//    ofLog() << "Prepare for Rendering";
//    
//    // setup vector field
//    m_vector_field.setup(m_input_provider->getWidth(), m_input_provider->getHeight(), 32);
//    // setup particle system
//    m_particle_system.setup(100, ofVec3f(m_input_provider->getWidth(), m_input_provider->getHeight(), 0.f));
//    
//    // update gui
//    m_ui.clearParameters();
//    m_ui.addParameters(m_input_provider->getGuiParams());
//    m_ui.addParameters(m_vector_field.getGuiParams());
//    m_ui.addParameters(m_particle_system.getGuiParams());
//    m_ui.loadSettings();
//}
//
//
////void ofApp::updateGuiPosition() {
////    float x = (((ofGetWindowWidth() - m_input_provider->getWidth()) / 2.f) - mGui.getWidth()) / 2.f;
////    float y = (ofGetWindowHeight() - mGui.getHeight()) / 2.f;
////    mGui.setPosition(x, y);
////}
//
//
////void ofApp::updateGui() {
////    mGui.clear();
////    mGui.setup("Timely Matter");
////    mGui.add(m_input_provider->getGuiParams());
////    mGui.add(m_vector_field.getGuiParams());
////    mGui.add(m_particle_system.getGuiParams());
////    mGui.loadFromFile("settings.xml");
////    
////    updateGuiPosition();
////}
//
//
////void ofApp::updateInputProvider(const VectorFieldInputType type) {
////    //
////    delete m_input_provider;
////    //
////    m_input_provider = m_input_factory.get(type);
////    m_input_provider->setup();
////    //
////    updateGui();
////}
//
