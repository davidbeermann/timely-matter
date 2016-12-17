#include "RenderView.hpp"
#include "AppMode.hpp"
#include "KinectInput.hpp"
#include "NoiseInput.hpp"
#include "AppConfig.hpp"

using namespace timelymatter;


RenderView::RenderView() : m_input(m_input_factory.get(m_app_model.getMode())) {
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
//    args.params.push_back(m_metaballs.getParams());
    ofParameterGroup & metaballs_params = m_metaballs.getParams();
    metaballs_params.add(m_metaballs_color.set("color", config.getMetaballsColor(), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255)));
    args.params.push_back(metaballs_params);
    
    ofParameterGroup blur_params;
    blur_params.setName("Gaussian Blur");
    blur_params.add(m_param_enabled.set("enabled", false));
    blur_params.add(m_param_strength.set("strength", 1, 0, 7));
    args.params.push_back(blur_params);
    
    ofParameterGroup render_params;
    render_params.setName("Rendering");
    render_params.add(m_param_input_visible.set("input visible", false));
    render_params.add(m_param_input_alpha.set("input alpha", 0.f, 0.f, 255.f));
    render_params.add(m_param_particles_update.set("particles update", true));
    render_params.add(m_param_particle_areas_visible.set("particle areas visible", false));
    render_params.add(m_param_particle_areas_alpha.set("particle areas alpha", 0.f, 0.f, 255.f));
    render_params.add(m_param_particle_cores_visible.set("particle cores visible", false));
    args.params.push_back(render_params);
    
    m_input_color.setHsb(0.f, 200.f, 255.f);
    m_particle_color.setHsb(0.f, 0.f, 255.f);
    
    ofNotifyEvent(m_view_event.update_gui, args, this);
}


void RenderView::m_onUpdate() {
    // update input pixels
    m_input.update();
    m_input_color.a = m_param_input_alpha;
    
    // ... before retrieving pixel data to update vector field.
    m_vector_field.update(m_input.getPixels());
    
    if (m_param_particles_update) {
        // apply forces of vector field to particl system...
        m_particle_system.applyVectorField(m_vector_field);

        // ...and update all particles within the system.
        // This also updates the output FBO.
        m_particle_system.update();
    
        // Pass particles to metaballs to calculate contour lines.
        // This also updates the output FBO.
        m_metaballs.update(m_particle_system.getParticles());
    }
}


void RenderView::m_onDraw() {
    // draw data input
    if (m_param_input_visible) {
        ofPushStyle();
        ofSetColor(m_input_color);
        m_input.getOutputFbo().draw(m_output_rect);
        ofPopStyle();
    }
    
    // draw output layers
    m_vector_field.getOutputFbo().draw(m_output_rect);
    
    // draw particle system
    if (m_param_particle_areas_visible) {
        m_particle_color.a = m_param_particle_areas_alpha;
        ofPushStyle();
        ofSetColor(m_particle_color);
        m_particle_system.getAreasFbo().draw(m_output_rect);
        ofPopStyle();
    }
    if (m_param_particle_cores_visible) {
        m_particle_color.a = 255.f;
        ofPushStyle();
        ofSetColor(m_particle_color);
        m_particle_system.getCoresFbo().draw(m_output_rect);
        ofPopStyle();
    }
//    m_particle_system.getOutputFbo().draw(m_output_rect);
    
    if (m_param_enabled) {
        // draw blurred metaballs
        // ----------------------
        m_blur_fbo.clear();
        
        // first pass of shader: horizontal blur
        m_blur_fbo.getPing().begin();
        m_blur_shader.begin();
        m_blur_shader.setUniform1i("uVertical", false); // HORIZONTAL
        m_blur_shader.setUniform1i("uStrength", m_param_strength);
        m_metaballs.getOutputFbo().draw(0, 0);
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
        m_metaballs.getOutputFbo().begin();
        ofClear(AppConfig::get().getBackgroundClearColor());
//        m_blur_fbo.getPing().draw(0, 0);
        m_blur_fbo.getPong().draw(0,0);
        m_metaballs.getOutputFbo().end();
    }
    
    // draw metaball fbo with correct color
    ofPushStyle();
    ofSetColor(ofColor(255, 0, 0, 128));
    m_metaballs.getWireframeFbo().draw(m_output_rect);
    ofSetColor(m_metaballs_color);
    m_metaballs.getOutputFbo().draw(m_output_rect);
    ofPopStyle();
}

