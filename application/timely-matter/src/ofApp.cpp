#include "ofApp.h"


void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(33);
    
    m_ui.setup();
    ofAddListener(m_ui.eventModeSelected, this, &ofApp::setInputProvider);
    
    m_input_provider = nullptr;
    
    m_update_window_size = false;
}


void ofApp::update() {
    if (m_update_window_size) {
        windowResized(ofGetWindowWidth(), ofGetWindowHeight());
        m_update_window_size = false;
    }
    
    if (isInputAvailable()) {
        // update input provider first ...
        m_input_provider->update();
        
        // ... before retrieving pixel data to update vector field.
        m_vector_field.update(m_input_provider->getPixels());
        
        // apply forces of vector field to particl system...
        m_particle_system.applyVectorField(m_vector_field);
        
        // ...and update all particles within the system.
        m_particle_system.update();
    }
    
    m_ui.update();
}


void ofApp::draw() {
    if (isInputAvailable()) {
        ofPushMatrix();
        ofTranslate(mCenteredPos);
        
        ofPushStyle();
        ofSetColor(0);
        ofDrawRectangle(0, 0, m_input_provider->getWidth(), m_input_provider->getHeight());
        ofPopStyle();
        
        m_input_provider->draw();
        m_vector_field.draw();
        m_particle_system.draw(m_vector_field);
        
        ofPopMatrix();
        
        // define debug info string
        string debugInfo = "FPS " + to_string((int) ofGetFrameRate());
        debugInfo += "\nActive Input Provider: " + m_input_provider->getName();
        debugInfo += "\n\nPress 'g' to toggle GUI";
        debugInfo += "\nPress '1' to switch to noise input";
        debugInfo += "\nPress '2' to switch to Kinect input";
        
        // show debug info
        ofDrawBitmapString(debugInfo, 10, 20);
    }
    
    m_ui.draw();
}


void ofApp::windowResized(int w, int h) {
    ofLog() << "ofApp::windowResized() --> " << w << "x" << h;
    mCenteredPos.set((w - m_input_provider->getWidth()) * 0.5f, (h - m_input_provider->getHeight()) * 0.5f);
}


void ofApp::setInputProvider(AppMode& mode) {
    if (isInputAvailable()) {
        delete m_input_provider;
        m_input_provider = nullptr;
    }
    
    m_input_provider = m_input_factory.get(mode);
    m_input_provider->setup();
    
    ofLog() << "input setup complete: " << m_input_provider->getName();
    
    //TODO fix this for switching between input providers
    // setup can not be done twice
    m_vector_field.setup(m_input_provider->getWidth(), m_input_provider->getHeight(), 32);
    
    m_particle_system.setup(100, ofVec3f(m_input_provider->getWidth(), m_input_provider->getHeight(), 0.f));
    
    // update gui
    m_ui.clearParameters();
    m_ui.addParameters(m_input_provider->getGuiParams());
    m_ui.addParameters(m_vector_field.getGuiParams());
    m_ui.addParameters(m_particle_system.getGuiParams());
    m_ui.loadSettings();

    // set flag to update window positions
    // not possible to do immediately because this method is called by ofController,
    // which apparently sets the window scope – window sizes are wrong when method is called.
    m_update_window_size = true;
}

const bool ofApp::isInputAvailable() {
    return m_input_provider != nullptr;
}


//void ofApp::updateGuiPosition() {
//    float x = (((ofGetWindowWidth() - m_input_provider->getWidth()) / 2.f) - mGui.getWidth()) / 2.f;
//    float y = (ofGetWindowHeight() - mGui.getHeight()) / 2.f;
//    mGui.setPosition(x, y);
//}


//void ofApp::updateGui() {
//    mGui.clear();
//    mGui.setup("Timely Matter");
//    mGui.add(m_input_provider->getGuiParams());
//    mGui.add(m_vector_field.getGuiParams());
//    mGui.add(m_particle_system.getGuiParams());
//    mGui.loadFromFile("settings.xml");
//    
//    updateGuiPosition();
//}


//void ofApp::updateInputProvider(const VectorFieldInputType type) {
//    //
//    delete m_input_provider;
//    //
//    m_input_provider = m_input_factory.get(type);
//    m_input_provider->setup();
//    //
//    updateGui();
//}

