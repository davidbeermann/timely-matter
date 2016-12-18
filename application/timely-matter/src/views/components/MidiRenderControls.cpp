#include "MidiRenderControls.hpp"

using namespace timelymatter;


MidiRenderControls::MidiRenderControls() {
    midiIn.openPort(0);
    midiIn.ignoreTypes();
    midiIn.addListener(this);
}


MidiRenderControls::~MidiRenderControls() {
    midiIn.closePort();
    midiIn.removeListener(this);
}


void MidiRenderControls::newMidiMessage(ofxMidiMessage& msg) {
    if (msg.control == 0) {
        evalKeyEvent(msg.pitch, msg.velocity);
    } else {
        evalControlEvent(msg.control, msg.value);
    }
}


void MidiRenderControls::evalKeyEvent(const int & pitch, const int & velocity) {
    bool key_down = velocity != 0;
    switch (pitch) {
        case 62: // key 1
            if (key_down) {
                m_params.getInputVisible() = !m_params.getInputVisible();
            }
            break;
        case 63: // key 2
            if (key_down) {
                m_params.getParticlesUpdate() = !m_params.getParticlesUpdate();
            }
            break;
        case 64: // key 3
            if (key_down) {
                m_params.getParticleAreasVisible() = !m_params.getParticleAreasVisible();
            }
            break;
        case 65: // key 4
            if (key_down) {
                m_params.getParticleCoresVisible() = !m_params.getParticleCoresVisible();
            }
            break;
        case 66: // key 5
            if (key_down) {
                m_params.getMetaballsMeshVisible() = !m_params.getMetaballsMeshVisible();
            }
            break;
        case 67: // key 6
            if (key_down) {
                m_params.getMetaballsWireframeVisible() = !m_params.getMetaballsWireframeVisible();
            }
            break;
        case 68: // key 7
            if (key_down) {
                m_params.getMetaballsInterpolate() = !m_params.getMetaballsInterpolate();
            }
            break;
        case 69: // key 8
            if (key_down) {
                m_params.getMetaballsInfill() = !m_params.getMetaballsInfill();
            }
            break;
        case 70: // key 9
            if (key_down) {
            }
            break;
        default:
            break;
    }
}


void MidiRenderControls::evalControlEvent(const int & control, const int & value) {
    float v = ofMap(value, 0.f, 127.f, 0.f, 255.f);
    switch (control) {
        case 40: // knob 1
            m_params.getInputAlpha() = v;
            break;
        case 71: // knob 2
            m_params.getParticleAreasAlpha() = v;
            break;
        case 79: // knob 3
            m_params.getMetaballsMeshAlpha() = v;
            break;
        default:
            break;
    }
}

