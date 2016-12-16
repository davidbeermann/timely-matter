#pragma once

#include "ofMain.h"
#include "ofxMidi.h"


namespace timelymatter {

    class RenderControls : public ofxMidiListener {
        ofParameter<bool> & m_input_visible;
        ofParameter<float> & m_input_alpha;
        ofxMidiIn midiIn;
    public:
        RenderControls(ofParameter<bool> & visible, ofParameter<float> & alpha);
        ~RenderControls();
        void newMidiMessage(ofxMidiMessage& msg);
    };
    
}

