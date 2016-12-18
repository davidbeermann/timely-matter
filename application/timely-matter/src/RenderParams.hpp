#pragma once

#include "ofMain.h"


namespace timelymatter {
    
    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class RenderParams {
        
        // private constructor
        RenderParams() {
            // setup parameters
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
        
        // available parameters
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
        // static method to retrieve singleton instance
        static RenderParams& get() {
            static RenderParams instance;
            return instance;
        }
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        RenderParams(RenderParams const&) = delete;
        void operator=(RenderParams const&) = delete;
        
        ofParameter<bool> & getInputVisible() {
            return m_input_visible;
        }
        ofParameter<float> & getInputAlpha() {
            return m_input_alpha;
        }
        ofParameter<bool> & getParticlesUpdate() {
            return m_particles_update;
        }
        ofParameter<bool> & getParticleAreasVisible() {
            return m_particle_areas_visible;
        }
        ofParameter<float> & getParticleAreasAlpha() {
            return m_particle_areas_alpha;
        }
        ofParameter<bool> & getParticleCoresVisible() {
            return m_particle_cores_visible;
        }
        ofParameter<bool> & getMetaballsMeshVisible() {
            return m_metaballs_mesh_visible;
        }
        ofParameter<float> & getMetaballsMeshAlpha() {
            return m_metaballs_mesh_alpha;
        }
        ofParameter<bool> & getMetaballsWireframeVisible() {
            return m_metaballs_wireframe_visible;
        }
        ofParameter<bool> & getMetaballsInterpolate() {
            return m_metaballs_interpolate;
        }
        ofParameter<bool> & getMetaballsInfill() {
            return m_metaballs_infill;
        }
        
    };
    
}