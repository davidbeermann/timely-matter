#pragma once

#include "ofMain.h"
#include "BaseView.hpp"
#include "VectorFieldInputFactory.hpp"
#include "VectorFieldInput.hpp"
#include "VectorField.hpp"
#include "ParticleSystem.hpp"
#include "Metaballs.hpp"


namespace timelymatter
{
    class RenderView : public BaseView {
        VectorFieldInputFactory m_input_factory;
        VectorFieldInput& m_input;
        VectorField m_vector_field;
        ParticleSystem m_particle_system;
        Metaballs m_metaballs;
        ofRectangle m_output_rect;
        ofFbo m_vector_field_fbo;
        ofFbo m_particle_system_fbo;
        ofFbo m_metaballs_fbo;
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
    public:
        RenderView();
    };
}