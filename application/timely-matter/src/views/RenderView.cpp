#include "RenderView.hpp"
#include "AppMode.hpp"
#include "KinectInput.hpp"
#include "NoiseInput.hpp"
#include "AppConfig.hpp"

using namespace timelymatter;


RenderView::RenderView() : m_params(RenderParams::get()), m_input(m_input_factory.get(m_app_model.getMode())) {
}


void RenderView::m_onWindowResized(const int width, const int height) {
    
    // set default output area
    m_output_rect.setSize(m_projector_model.getOutputWidth(), m_projector_model.getOutputHeight());
    
    if (m_output_rect.getWidth() == width && m_output_rect.getHeight() == height) {
        // reset position when output size matches window size
        m_output_rect.setPosition(0, 0);
    } else {
        // calculate scaling for smaller screens/windows
        float scale = 1.f; // default scale
        if (width < m_output_rect.getWidth() || height < m_output_rect.getHeight()) {
            float scale_x = (float) width / m_output_rect.getWidth();
            float scale_y = (float) height / m_output_rect.getHeight();
            scale = scale_x < scale_y ? scale_x : scale_y;
            m_output_rect.scale(scale);
        }
        
        // calculate centered position
        int x = (width - m_output_rect.getWidth()) * 0.5f;
        int y = (height - m_output_rect.getHeight()) * 0.5f;
        m_output_rect.setPosition(x, y);
    }
    
}


void RenderView::m_onSetup() {
    
#ifdef USING_OSC
    m_osc_controls.setup();
#endif
    
    m_input.setup();
    
    AppConfig & config = AppConfig::get();
    
    // setup vector field
    m_vector_field.setup(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), m_input.getWidth(), m_input.getHeight(), config.getVectorFieldSubdivisionX(), config.getVectorFieldSubdivisionY());
    
    // setup particle system
    m_particle_system.setup(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), config.getParticleSystemCount(), config.getParticleSystemMinRadius(), config.getParticleSystemMaxRadius());
    
    // setup metaballs
    m_metaballs.setup(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight(), config.getMarchingSquaresColumns(), config.getMarchingSquaresRows());
    
    // setup shader
    m_blur_fbo.allocate(m_projector_model.getBufferWidth(), m_projector_model.getBufferHeight());
    m_blur_fbo.clear();
    m_blur_shader.load("gaussian_blur.vert", "gaussian_blur.frag");
    
    // compile gui params
    GuiUpdateArgs args;
    args.params.push_back(m_input.getParams());
    args.params.push_back(m_vector_field.getParams());
    args.params.push_back(m_particle_system.getParams());
    
    // add params for metaballs
    args.params.push_back(m_metaballs.getParams());
    
    ofParameterGroup blur_params;
    blur_params.setName("Gaussian Blur");
    blur_params.add(m_param_enabled.set("enabled", false));
    blur_params.add(m_param_strength.set("strength", 1, 0, 7));
    args.params.push_back(blur_params);
    
    ofParameterGroup render_params;
    render_params.setName("Rendering");
    render_params.add(m_params.getInputVisible());
    render_params.add(m_params.getInputAlpha());
    render_params.add(m_params.getInputVisible());
    render_params.add(m_params.getInputAlpha());
    render_params.add(m_params.getParticlesUpdate());
    render_params.add(m_params.getParticleAreasVisible());
    render_params.add(m_params.getParticleAreasAlpha());
    render_params.add(m_params.getParticleCoresVisible());
    render_params.add(m_params.getMetaballsMeshVisible());
    render_params.add(m_params.getMetaballsMeshAlpha());
    render_params.add(m_params.getMetaballsWireframeVisible());
    render_params.add(m_params.getMetaballsInterpolate());
    render_params.add(m_params.getMetaballsInfill());
    args.params.push_back(render_params);
    
    m_input_color.setHsb(0.f, 200.f, 255.f); // desaturated red
    m_particle_color.setHsb(0.f, 0.f, 255.f); // bright white
    m_metaballs_color.setHsb(0.f, 0.f, 255.f); // bright white
    
    ofNotifyEvent(m_view_event.update_gui, args, this);
}


void RenderView::m_onUpdate() {
    
#ifdef USING_OSC
    // update controls before anything else.
    // it updates the parameters!
    m_osc_controls.update();
#endif
    
    // update input pixels
    m_input.update();
    m_input_color.a = m_params.getInputAlpha();
    
    // ... before retrieving pixel data to update vector field.
    m_vector_field.update(m_input.getPixels());
    
    if (m_params.getParticlesUpdate()) {
        // apply forces of vector field to particl system...
        m_particle_system.applyVectorField(m_vector_field);

        // ...and update all particles within the system.
        // This also updates the output FBO.
        m_particle_system.update();
        
        // set metaballs parameters
        m_metaballs.setThreshold(m_params.getMetaballsThreshold());
        m_metaballs.setDampening(m_params.getMetaballsDampening());
        m_metaballs.setInterpolation(m_params.getMetaballsInterpolate());
        m_metaballs.setInfill(m_params.getMetaballsInfill());
        
        // Pass particles to metaballs to calculate contour lines.
        // This also updates the output FBO.
        m_metaballs.update(m_particle_system.getParticles());
    }
}


void RenderView::m_onDraw() {
    // draw data input
    if (m_params.getInputVisible()) {
        ofPushStyle();
        ofSetColor(m_input_color);
        m_input.getOutputFbo().draw(m_output_rect);
        ofPopStyle();
    }
    
    // draw output layers
    m_vector_field.getOutputFbo().draw(m_output_rect);
    
    // draw particle system
    if (m_params.getParticleAreasVisible()) {
        m_particle_color.a = m_params.getParticleAreasAlpha();
        ofPushStyle();
        ofSetColor(m_particle_color);
        m_particle_system.getAreasFbo().draw(m_output_rect);
        ofPopStyle();
    }
    if (m_params.getParticleCoresVisible()) {
        m_particle_color.a = m_params.getParticleCoresAlpha();
        ofPushStyle();
        ofSetColor(m_particle_color);
        m_particle_system.getCoresFbo().draw(m_output_rect);
        ofPopStyle();
    }
    
    if (m_param_enabled) {
        // draw blurred metaballs
        // ----------------------
        m_blur_fbo.clear();
        
        // first pass of shader: horizontal blur
        m_blur_fbo.getPing().begin();
        m_blur_shader.begin();
        m_blur_shader.setUniform1i("uVertical", false); // HORIZONTAL
        m_blur_shader.setUniform1i("uStrength", m_param_strength);
        m_metaballs.getMeshFbo().draw(0, 0);
        m_blur_shader.end();
        m_blur_fbo.getPing().end();
        
        // second pass of shader: vertical blur
        m_blur_fbo.getPong().begin();
        m_blur_shader.begin();
        m_blur_shader.setUniform1i("uVertical", true); // VERTICAL
        m_blur_shader.setUniform1i("uStrength", m_param_strength);
        m_blur_fbo.getPing().draw(0, 0);
        m_blur_shader.end();
        m_blur_fbo.getPong().end();
        
        // swap buffers: pong -> ping
        //TODO swapping causes visual jitter and somehow neglects metaballs updates.
//        m_blur_fbo.swap();
        
        // draw result of shader back to input fbo
        m_metaballs.getMeshFbo().begin();
        ofClear(AppConfig::get().getBackgroundClearColor());
//        m_blur_fbo.getPing().draw(0, 0);
        m_blur_fbo.getPong().draw(0,0);
        m_metaballs.getMeshFbo().end();
    }
    
    // draw metaball fbos with correct color
    ofPushStyle();
    if (m_params.getMetaballsWireframeVisible()) {
        m_metaballs_color.a = m_params.getMetaballsWireframeAlpha();
        ofSetColor(m_metaballs_color);
        m_metaballs.getWireframeFbo().draw(m_output_rect);
    }
    if (m_params.getMetaballsMeshVisible()) {
        m_metaballs_color.a = m_params.getMetaballsMeshAlpha();
        ofSetColor(m_metaballs_color);
        m_metaballs.getMeshFbo().draw(m_output_rect);
    }
    ofPopStyle();
}

