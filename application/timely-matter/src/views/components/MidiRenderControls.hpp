#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "RenderControls.hpp"


namespace timelymatter {

    class MidiRenderControls : public ofxMidiListener, public RenderControls {
        void evalKeyEvent(const int & pitch, const int & velocity);
        void evalControlEvent(const int & control, const int & value);
        
        ofxMidiIn midiIn;
        
    protected:
        // implementation of abstract class methods
        void m_onSetup() {};
        void m_onUpdate() {};
        
    public:
        MidiRenderControls();
        ~MidiRenderControls();
        
        void newMidiMessage(ofxMidiMessage& msg);
    
    };
    
}

