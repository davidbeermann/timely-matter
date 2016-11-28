#include "RenderView.hpp"
#include "AppMode.hpp"
#include "KinectInput.hpp"
#include "NoiseInput.hpp"

#define PARTICLE_COUNT 100

using namespace timelymatter;


RenderView::RenderView() : m_input(m_input_factory.get(m_app_model.getMode())) {
}


void RenderView::m_onWindowResized(const int width, const int height) {
    m_center_position.set((width - m_projector_model.getWidth()) * 0.5f, (height - m_projector_model.getHeight()) * 0.5f);
}


void RenderView::m_onSetup() {
    m_input.setup();
    
    // setup vector field
    m_vector_field.setup(m_projector_model.getWidth(), m_projector_model.getHeight(), m_input.getWidth(), m_input.getHeight(), 32);
    
    // setup particle system
    m_particle_system.setup(PARTICLE_COUNT, ofVec3f(m_projector_model.getWidth(), m_projector_model.getHeight(), 0.f));
    
    // setup metaballs
    m_metaballs.setup(m_projector_model.getWidth(), m_projector_model.getHeight());
    
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
}


void RenderView::m_onDraw() {
    ofPushMatrix();
    ofTranslate(m_center_position);
    
    ofPushStyle();
    ofSetColor(0);
    ofDrawRectangle(m_projector_model.getSize());
    ofPopStyle();
    
    m_input.draw(m_projector_model.getSize());
    m_vector_field.draw();
    m_particle_system.draw(m_vector_field);
    m_metaballs.draw();
    
    ofPopMatrix();
}

