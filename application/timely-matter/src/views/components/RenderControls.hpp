#pragma once

#include "ofMain.h"
#include "ofxMidi.h"


namespace timelymatter {

    class RenderControls : public ofxMidiListener {
        void evalKeyEvent(const int & pitch, const int & velocity);
        void evalControlEvent(const int & control, const int & value);
        ofParameter<bool> & m_input_visible;
        ofParameter<float> & m_input_alpha;
        ofParameter<bool> & m_particles_update;
        ofParameter<bool> & m_particle_areas_visible;
        ofParameter<float> & m_particle_areas_alpha;
        ofParameter<bool> & m_particle_cores_visible;
        ofxMidiIn midiIn;
    public:
        RenderControls(
            ofParameter<bool> & input_visible, ofParameter<float> & input_alpha,
            ofParameter<bool> & particles_update,
            ofParameter<bool> & particle_areas_visible, ofParameter<float> & particle_areas_alpha,
            ofParameter<bool> & particle_cores_visible
        );
        ~RenderControls();
        void newMidiMessage(ofxMidiMessage& msg);
    };
    
}

