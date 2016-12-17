#include "RenderControls.hpp"

using namespace timelymatter;



RenderControls::RenderControls() {
    midiIn.openPort(0);
    midiIn.ignoreTypes();
    midiIn.addListener(this);
    
    m_input_visible.set("input visible", false);
    m_input_alpha.set("input alpha", 0.f, 0.f, 255.f);
    m_particles_update.set("particles update", true);
    m_particle_areas_visible.set("particle areas visible", false);
    m_particle_areas_alpha.set("particle areas alpha", 0.f, 0.f, 255.f);
    m_particle_cores_visible.set("particle cores visible", false);
    m_metaballs_mesh_visible.set("metaballs mesh visible", true);
    m_metaballs_mesh_alpha.set("metaballs mesh alpha", 0.f, 0.f, 255.f);
    m_metaballs_wireframe_visible.set("metaballs wireframe visible", false);
    m_metaballs_interpolate.set("metaballs interpolate", true);
    m_metaballs_infill.set("metaballs infill", true);
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
        case 66: // key 5
            if (key_down) {
                m_metaballs_mesh_visible = !m_metaballs_mesh_visible;
            }
            break;
        case 67: // key 6
            if (key_down) {
                m_metaballs_wireframe_visible = !m_metaballs_wireframe_visible;
            }
            break;
        case 68: // key 7
            if (key_down) {
                m_metaballs_interpolate = !m_metaballs_interpolate;
            }
            break;
        case 69: // key 8
            if (key_down) {
                m_metaballs_infill = !m_metaballs_infill;
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


void RenderControls::evalControlEvent(const int & control, const int & value) {
    float v = ofMap(value, 0.f, 127.f, 0.f, 255.f);
    switch (control) {
        case 40: // knob 1
            m_input_alpha = v;
            break;
        case 71: // knob 2
            m_particle_areas_alpha = v;
            break;
        case 79: // knob 3
            m_metaballs_mesh_alpha = v;
            break;
        default:
            break;
    }
}

