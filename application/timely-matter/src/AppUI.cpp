#include "AppUI.hpp"


void AppUI::setup() {
    // configure gui
    m_gui.setDefaultWidth(250);
    m_gui.setWidthElements(250);
    m_gui.setup("Timely Matter");
    m_gui_visible = false;
    
    // set initial state
    m_state = AppState::MODE_SELECTION;
}


void AppUI::update() {
    m_debug_info = "FPS: " + to_string((int) ofGetFrameRate());
}


void AppUI::draw() {
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


void AppUI::keyPressed(ofKeyEventArgs& args) {
    switch (args.key) {
        case 'g':
            // toggle gui display
            m_gui_visible = !m_gui_visible;
            break;
    }
    
    switch (m_state) {
        case AppState::MODE_SELECTION:
            m_evalModeSelectionInput(args.key);
            break;
        case AppState::CAMERA_ADJUSTMENT:
            break;
        case AppState::DEPTH_ADJUSTMENT:
            break;
        case AppState::RUNNING:
            break;
    }
}


void AppUI::clearParameters() {
    m_gui.clear();
}


void AppUI::addParameters(const ofParameterGroup& group) {
    m_gui.add(group);
}


void AppUI::loadSettings() {
    m_gui.loadFromFile("settings.xml");
}


void AppUI::m_drawModeSelectionView() {
    string info = "SELECT APPLICATION MODE";
    info += "\n- Press '1' for Noise";
    info += "\n- Press '2' for Kinect";
    
    ofDrawBitmapString(info, 20, 40);
}


void AppUI::m_evalModeSelectionInput(int selection) {
    switch (selection) {
        case '1':
            ofLog() << "Application mode selected: NOISE";
            m_setupMode(AppMode::NOISE);
            break;
            
        case '2':
            ofLog() << "Application mode selected: KINECT";
            m_setupMode(AppMode::KINECT);
            break;
            
        default:
            ofLog() << "Invalid selection in this mode";
            break;
    }
}


void AppUI::m_setupMode(AppMode mode) {
    m_mode = mode;
    ofNotifyEvent(eventModeSelected, m_mode, this);
}
