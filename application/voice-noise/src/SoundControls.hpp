#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "SoundParams.hpp"

    
class SoundControls {
    
    // parameter reference
    SoundParams & m_params;
    
    // configuration from XML file
    ofxXmlSettings m_config;
    
    // osc interfaces
    ofxOscReceiver m_receiver;
    ofxOscSender m_sender;
    
    void sendInitialStatus();
    
public:
    SoundControls() : m_params(SoundParams::get()) {
    }
    
    // implementation of abstract class methods
    void setup();
    void update();
    
};