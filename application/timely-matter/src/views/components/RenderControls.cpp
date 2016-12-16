#include "RenderControls.hpp"

using namespace timelymatter;



RenderControls::RenderControls(ofParameter<bool> & visible, ofParameter<float> & alpha) :m_input_visible(visible), m_input_alpha(alpha)
{
    midiIn.openPort(0);
    midiIn.ignoreTypes();
    midiIn.addListener(this);
}


RenderControls::~RenderControls() {
    midiIn.closePort();
    midiIn.removeListener(this);
}


void RenderControls::newMidiMessage(ofxMidiMessage& msg) {
    if (msg.control == 0) {
        switch (msg.pitch) {
            case 62:
                if (msg.velocity != 0) {
                    m_input_visible = !m_input_visible;
                }
                break;
            default:
                break;
        }
    } else {
        switch (msg.control) {
            case 40:
                m_input_alpha = ofMap(msg.value, 0.f, 127.f, 0.f, 255.f);
                break;
            default:
                break;
        }
    }
    
//    ofLog() << msg.pitch << " " << msg.control;
}

