#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "RenderControls.hpp"


namespace timelymatter {

    class OscRenderControls : public RenderControls {
        
        ofxOscReceiver m_receiver;
        
    protected:
        // implementation of abstract class methods
        void m_onSetup();
        void m_onUpdate();
        
    };

}