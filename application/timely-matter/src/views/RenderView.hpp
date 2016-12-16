#pragma once

#include "ofMain.h"
#include "BaseView.hpp"
#include "VectorFieldInputFactory.hpp"
#include "VectorFieldInput.hpp"
#include "VectorField.hpp"
#include "ParticleSystem.hpp"
#include "Metaballs.hpp"
#include "PingPongFbo.hpp"
#include "RenderControls.hpp"


namespace timelymatter
{
    class RenderView : public BaseView {
        VectorFieldInputFactory m_input_factory;
        VectorFieldInput& m_input;
        VectorField m_vector_field;
        ParticleSystem m_particle_system;
        Metaballs m_metaballs;
        ofRectangle m_output_rect;
        
        ofParameter<ofColor> m_metaballs_color;
        
        PingPongFbo m_blur_fbo;
        ofShader m_blur_shader;
        ofParameter<bool> m_param_enabled;
        ofParameter<int> m_param_strength;
        
        ofParameter<bool> m_param_input_visible;
        ofParameter<float> m_param_input_alpha;
        
        ofColor m_input_color;
        
        RenderControls m_controls = RenderControls(m_param_input_visible, m_param_input_alpha);
        
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
    public:
        RenderView();
    };
}