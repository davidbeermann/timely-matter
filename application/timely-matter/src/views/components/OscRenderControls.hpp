#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "RenderControls.hpp"


namespace timelymatter {

    class OscRenderControls : public RenderControls {
        
        // configuration from XML file
        ofxXmlSettings m_config;
        
        // osc interfaces
        ofxOscReceiver m_receiver;
        ofxOscSender m_sender;
        
        void sendInitialStatus();
        
    protected:
        // implementation of abstract class methods
        void m_onSetup();
        void m_onUpdate();
        
    };

}