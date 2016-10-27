#include "GaussianBlurFxModule.hpp"


void GaussianBlurFxModule::doInit(const unsigned int width, const unsigned int height) {
    m_ping_pong_fbo.allocate(width, height);
    m_ping_pong_fbo.clear();
    
    // 2-pass Gaussian Blur shader
    m_shader.load("shaders/gaussian_blur.vert", "shaders/gaussian_blur.frag");
    
    m_params.setName("Gaussian Blur");
    m_params.add(m_param_enabled.set("enabled", true));
    m_params.add(m_param_strength.set("strength", 1, 0, 7));
}


void GaussianBlurFxModule::doRender(ofFbo& input) {
    if (m_param_enabled) {
        
        // first pass of shader: horizontal blur
        m_ping_pong_fbo.getPing().begin();
        ofClear(0.f);
        m_shader.begin();
        m_shader.setUniform1i("uVertical", false); // HORIZONTAL
        m_shader.setUniform1i("uStrength", m_param_strength);
        input.draw(0, 0);
        m_shader.end();
        m_ping_pong_fbo.getPing().end();
        
        // second pass of shader: vertical blur
        m_ping_pong_fbo.getPong().begin();
        ofClear(0.f);
        m_shader.begin();
        m_shader.setUniform1i("uVertical", true); // VERTICAL
        m_shader.setUniform1i("uStrength", m_param_strength);
        m_ping_pong_fbo.getPing().draw(0, 0);
        m_shader.end();
        m_ping_pong_fbo.getPong().end();
        
        // swap buffers: pong -> ping
        m_ping_pong_fbo.swap();
        
        // draw result of shader back to input fbo
        input.begin();
        ofClear(0.f);
        m_ping_pong_fbo.getPing().draw(0, 0);
        input.end();
    }
}
