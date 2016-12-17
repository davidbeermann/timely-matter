#pragma once

#include "ofMain.h"
#include "ofxMidi.h"


namespace timelymatter {

    class RenderControls : public ofxMidiListener {
        void evalKeyEvent(const int & pitch, const int & velocity);
        void evalControlEvent(const int & control, const int & value);
        
        ofxMidiIn midiIn;
        
        ofParameter<bool> m_input_visible;
        ofParameter<float> m_input_alpha;
        ofParameter<bool> m_particles_update;
        ofParameter<bool> m_particle_areas_visible;
        ofParameter<float> m_particle_areas_alpha;
        ofParameter<bool> m_particle_cores_visible;
        ofParameter<bool> m_metaballs_mesh_visible;
        ofParameter<float> m_metaballs_mesh_alpha;
        ofParameter<bool> m_metaballs_wireframe_visible;
        ofParameter<bool> m_metaballs_interpolate;
        ofParameter<bool> m_metaballs_infill;
        
    public:
        RenderControls();
        ~RenderControls();
        
        void newMidiMessage(ofxMidiMessage& msg);
        
        ofParameter<bool> & getParamInputVisible() {
            return m_input_visible;
        }
        ofParameter<float> & getParamInputAlpha() {
            return m_input_alpha;
        }
        ofParameter<bool> & getParamParticlesUpdate() {
            return m_particles_update;
        }
        ofParameter<bool> & getParamParticleAreasVisible() {
            return m_particle_areas_visible;
        }
        ofParameter<float> & getParamParticleAreasAlpha() {
            return m_particle_areas_alpha;
        }
        ofParameter<bool> & getParamParticleCoresVisible() {
            return m_particle_cores_visible;
        }
        ofParameter<bool> & getParamMetaballsMeshVisible() {
            return m_metaballs_mesh_visible;
        }
        ofParameter<float> & getParamMetaballsMeshAlpha() {
            return m_metaballs_mesh_alpha;
        }
        ofParameter<bool> & getParamMetaballsWireframeVisible() {
            return m_metaballs_wireframe_visible;
        }
        ofParameter<bool> & getParamMetaballsInterpolate() {
            return m_metaballs_interpolate;
        }
        ofParameter<bool> & getParamMetaballsInfill() {
            return m_metaballs_infill;
        }
    };
    
}

