#include "RenderView.hpp"
#include "AppMode.hpp"
#include "KinectInput.hpp"
#include "NoiseInput.hpp"
#include "AppConfig.hpp"

using namespace timelymatter;


RenderView::RenderView() : m_input(m_input_factory.get(m_app_model.getMode())) {
}


void RenderView::m_onWindowResized(const int width, const int height) {
    int x = (width - m_output_rect.getWidth()) * 0.5f;
    int y = (height - m_output_rect.getHeight()) * 0.5f;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    
    m_output_rect.setPosition(x, y);
}


void RenderView::m_onSetup() {
    m_input.setup();
    
    // setup vector field
    m_vector_field.setup(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), m_input.getWidth(), m_input.getHeight(), AppConfig::get().getVectorFieldSubdivisionX(), AppConfig::get().getVectorFieldSubdivisionY());
    
    // setup particle system
    m_particle_system.setup(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), AppConfig::get().getParticleSystemCount(), AppConfig::get().getParticleSystemMinRadius(), AppConfig::get().getParticleSystemMaxRadius());
    
    // setup metaballs
    m_metaballs.setup(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), AppConfig::get().getMarchingSquaresColumns(), AppConfig::get().getMarchingSquaresRows());
    
    // define output area
    m_output_rect.setSize(m_projector_model.getOutputWidth(), m_projector_model.getOutputHeight());
    
    // allocate FBOs
    m_vector_field_fbo.allocate(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), GL_RGBA, 4);
    m_particle_system_fbo.allocate(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), GL_RGBA, 4);
    m_metaballs_fbo.allocate(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), GL_RGBA, 4);
    
    // compile gui params
    GuiUpdateArgs args;
    args.params.push_back(m_input.getParams());
    args.params.push_back(m_vector_field.getParams());
    args.params.push_back(m_particle_system.getParams());
    args.params.push_back(m_metaballs.getParams());
    
    ofNotifyEvent(m_view_event.update_gui, args, this);
}


void RenderView::m_onUpdate() {
    // update input pixels
    m_input.update();
    
    // ... before retrieving pixel data to update vector field.
    m_vector_field.update(m_input.getPixels());

    // apply forces of vector field to particl system...
    m_particle_system.applyVectorField(m_vector_field);

    // ...and update all particles within the system.
    m_particle_system.update();
    
    // pass particles to metaballs to calculate contour lines
    m_metaballs.update(m_particle_system.getParticles());
    
    // update FBOs
    m_vector_field_fbo.begin();
    ofClear(0);
    m_vector_field.draw();
    m_vector_field_fbo.end();
    
    m_particle_system_fbo.begin();
    ofClear(0);
    m_particle_system.draw(m_vector_field);
    m_particle_system_fbo.end();
    
    m_metaballs_fbo.begin();
    ofClear(0);
    m_metaballs.draw();
    m_metaballs_fbo.end();
}


void RenderView::m_onDraw() {
    // draw black background
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(m_output_rect);
    ofPopStyle();
    
    // draw data input to background
    m_input.draw(m_output_rect);
    
    // draw output layers
    m_vector_field_fbo.draw(m_output_rect);
    m_particle_system_fbo.draw(m_output_rect);
    m_metaballs_fbo.draw(m_output_rect);
}

