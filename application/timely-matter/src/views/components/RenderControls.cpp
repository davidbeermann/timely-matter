#include "RenderControls.hpp"

using namespace timelymatter;



RenderControls::RenderControls(
    ofParameter<bool> & input_visible, ofParameter<float> & input_alpha,
    ofParameter<bool> & particles_update,
    ofParameter<bool> & particle_areas_visible, ofParameter<float> & particle_areas_alpha,
    ofParameter<bool> & particle_cores_visible
)
: m_input_visible(input_visible)
, m_input_alpha(input_alpha)
, m_particles_update(particles_update)
, m_particle_areas_visible(particle_areas_visible)
, m_particle_areas_alpha(particle_areas_alpha)
, m_particle_cores_visible(particle_cores_visible)
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
        evalKeyEvent(msg.pitch, msg.velocity);
    } else {
        evalControlEvent(msg.control, msg.value);
    }
}



void RenderControls::evalKeyEvent(const int & pitch, const int & velocity) {
    bool key_down = velocity != 0;
    switch (pitch) {
        case 62: // key 1
            if (key_down) {
                m_input_visible = !m_input_visible;
            }
            break;
        case 63: // key 2
            if (key_down) {
                m_particles_update = !m_particles_update;
            }
            break;
        case 64: // key 3
            if (key_down) {
                m_particle_areas_visible = !m_particle_areas_visible;
            }
            break;
        case 65: // key 4
            if (key_down) {
                m_particle_cores_visible = !m_particle_cores_visible;
            }
            break;
        default:
            break;
    }
}


void RenderControls::evalControlEvent(const int & control, const int & value) {
    float v = ofMap(value, 0.f, 127.f, 0.f, 255.f);
    switch (control) {
        case 40: // knob 1
            m_input_alpha = v;
            break;
        case 71: // knob 2
            m_particle_areas_alpha = v;
            break;
        default:
            break;
    }
}

