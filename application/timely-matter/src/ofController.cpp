#include "ofController.hpp"


void ofController::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(33);
    ofSetBackgroundAuto(true);
    
    // configure gui
    m_gui.setDefaultWidth(250);
    m_gui.setWidthElements(250);
    m_gui.setup("Timely Matter");
    m_gui_visible = false;
    
    // set initial state
    m_state = AppState::MODE_SELECTION;
}


void ofController::update() {
    m_debug_info = "FPS: " + to_string((int) ofGetFrameRate());
}


void ofController::draw() {
    ofDrawBitmapString(m_debug_info, 20, 20);
    
    switch (m_state) {
        case AppState::MODE_SELECTION:
            m_drawModeSelectionView();
            break;
        case AppState::CAMERA_ADJUSTMENT:
            break;
        case AppState::DEPTH_ADJUSTMENT:
            break;
        case AppState::RUNNING:
            break;
    }
    
    if (m_gui_visible) {
        m_gui.draw();
    }
}


void ofController::keyReleased(int key) {
    switch (key) {
        case 'g':
            // toggle gui display
            m_gui_visible = !m_gui_visible;
            break;
    }
    
    switch (m_state) {
        case AppState::MODE_SELECTION:
            m_evalModeSelectionInput(key);
            break;
        case AppState::CAMERA_ADJUSTMENT:
            break;
        case AppState::DEPTH_ADJUSTMENT:
            break;
        case AppState::RUNNING:
            break;
    }
}


void ofController::m_drawModeSelectionView() {
    string info = "SELECT APPLICATION MODE";
    info += "\n- Press '1' for Noise";
    info += "\n- Press '2' for Kinect";
    
    ofDrawBitmapString(info, 20, 40);
}


void ofController::m_evalModeSelectionInput(int selection) {
    switch (selection) {
        case '1':
            m_mode = AppMode::NOISE;
            ofLog() << "Application mode selected: NOISE";
            m_setupMode();
            break;
            
        case '2':
            m_mode = AppMode::KINECT;
            ofLog() << "Application mode selected: KINECT";
            m_setupMode();
            break;
            
        default:
            ofLog() << "Invalid selection in this mode";
            break;
    }
}


void ofController::m_setupMode() {
    // notify app about mode selection
    app_sptr->setInputProvider(m_mode);
    // reflect changes in app input in gui
    m_updateGuiParams();
}


void ofController::m_updateGuiParams() {
    m_gui.clear();
    if (app_sptr->isInputAvailable()) {
        m_gui.add(app_sptr->getInputParams());
        m_gui.add(app_sptr->getVectorFieldParams());
        m_gui.add(app_sptr->getParticleSystemParams());
        m_gui.loadFromFile("settings.xml");
    } else {
        ofLog() << "Can not update GUI because no input is available.";
    }
}
