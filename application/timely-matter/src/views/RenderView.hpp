#pragma once

#include "ofMain.h"
#include "BaseView.hpp"
#include "RenderParams.hpp"
#include "VectorFieldInputFactory.hpp"
#include "VectorFieldInput.hpp"
#include "VectorField.hpp"
#include "ParticleSystem.hpp"
#include "Metaballs.hpp"
#include "PingPongFbo.hpp"
#include "RenderControls.hpp"
#include "OscRenderControls.hpp"
#include "MidiRenderControls.hpp"
#include "PdfRenderer.hpp"


namespace timelymatter
{
    class RenderView : public BaseView {
        
        RenderParams & m_params;
        VectorFieldInputFactory m_input_factory;
        VectorFieldInput& m_input;
        VectorField m_vector_field;
        ParticleSystem m_particle_system;
        Metaballs m_metaballs;
        ofRectangle m_output_rect;
        
        PingPongFbo m_blur_fbo;
        ofShader m_blur_shader;
        ofParameter<bool> m_param_enabled;
        ofParameter<int> m_param_strength;
        
        ofColor m_input_color;
        ofColor m_particle_color;
        ofColor m_metaballs_color;
        
        OscRenderControls m_osc_controls = OscRenderControls();
        PdfRenderer m_pdf_renderer;
        
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
        
    public:
        RenderView();
        
    };
}