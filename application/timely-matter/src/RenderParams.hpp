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
            
            m_particles_update.set("update", true);
            m_particle_areas_visible.set("areas visible", false);
            m_particle_areas_alpha.set("areas alpha", 0.f, 0.f, 255.f);
            m_particle_cores_visible.set("cores visible", false);
            m_particle_cores_alpha.set("cores alpha", 0.f, 0.f, 255.f);
            
            m_metaballs_infill.set("infill", true);
            m_metaballs_mesh_visible.set("mesh visible", true);
            m_metaballs_mesh_alpha.set("mesh alpha", 0.f, 0.f, 255.f);
            m_metaballs_wireframe_visible.set("wireframe visible", false);
            m_metaballs_wireframe_alpha.set("wireframe alpha", 0.f, 0.f, 255.f);
            m_metaballs_interpolate.set("interpolate", true);
            m_metaballs_fitness.set("fitness", 0.f, 0.f, 1.f);
            m_metaballs_threshold.set("threshold", 0.f, 0.f, 1.f);
            m_metaballs_dampening.set("dampening", 0.5f, 0.f, 1.f);
            
            m_input_params.setName("Depth Input");
            m_input_params.add(m_input_visible);
            m_input_params.add(m_input_alpha);
            
            m_particle_params.setName("Particles");
            m_particle_params.add(m_particles_update);
            m_particle_params.add(m_particle_areas_visible);
            m_particle_params.add(m_particle_areas_alpha);
            m_particle_params.add(m_particle_cores_visible);
            m_particle_params.add(m_particle_cores_alpha);
            
            m_metaball_params.setName("Metaballs");
            m_metaball_params.add(m_metaballs_infill);
            m_metaball_params.add(m_metaballs_mesh_visible);
            m_metaball_params.add(m_metaballs_mesh_alpha);
            m_metaball_params.add(m_metaballs_wireframe_visible);
            m_metaball_params.add(m_metaballs_wireframe_alpha);
            m_metaball_params.add(m_metaballs_interpolate);
            m_metaball_params.add(m_metaballs_fitness);
            m_metaball_params.add(m_metaballs_threshold);
            m_metaball_params.add(m_metaballs_dampening);
        }
        
        // available parameters
        ofParameter<bool> m_input_visible;
        ofParameter<float> m_input_alpha;
        
        ofParameter<bool> m_particles_update;
        ofParameter<bool> m_particle_areas_visible;
        ofParameter<float> m_particle_areas_alpha;
        ofParameter<bool> m_particle_cores_visible;
        ofParameter<float> m_particle_cores_alpha;
        
        ofParameter<bool> m_metaballs_infill;
        ofParameter<bool> m_metaballs_mesh_visible;
        ofParameter<float> m_metaballs_mesh_alpha;
        ofParameter<bool> m_metaballs_wireframe_visible;
        ofParameter<float> m_metaballs_wireframe_alpha;
        ofParameter<bool> m_metaballs_interpolate;
        ofParameter<float> m_metaballs_fitness;
        ofParameter<float> m_metaballs_threshold;
        ofParameter<float> m_metaballs_dampening;
        
        ofParameterGroup m_input_params;
        ofParameterGroup m_particle_params;
        ofParameterGroup m_metaball_params;

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
        ofParameter<float> & getParticleCoresAlpha() {
            return m_particle_cores_alpha;
        }
        
        ofParameter<bool> & getMetaballsInfill() {
            return m_metaballs_infill;
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
        ofParameter<float> & getMetaballsWireframeAlpha() {
            return m_metaballs_wireframe_alpha;
        }
        ofParameter<bool> & getMetaballsInterpolate() {
            return m_metaballs_interpolate;
        }
        ofParameter<float> & getMetaballsFitness() {
            return m_metaballs_fitness;
        }
        ofParameter<float> & getMetaballsThreshold() {
            return m_metaballs_threshold;
        }
        ofParameter<float> & getMetaballsDampening() {
            return m_metaballs_dampening;
        }
        
        ofParameterGroup & getInputParams() {
            return m_input_params;
        }
        ofParameterGroup & getParticleParams() {
            return m_particle_params;
        }
        ofParameterGroup & getMetaballParams() {
            return m_metaball_params;
        }
        
    };
    
}