#include "PerlinNoiseFbo.hpp"


void PerlinNoiseFbo::setup(const int& width, const int& height) {
    // load vertex and fragment shaders
    // the vertex shader doesn't really do anything.
    // all the magic is happening in the fragment shader.
    m_shader.load("perlin.vert", "perlin.frag");
    
    // initialize off-screen fbo
    m_fbo.allocate(width, height);
    m_image.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    
    // clear frame buffer
    m_fbo.begin();
    ofClear(0);
    m_fbo.end();
    
    // prepare gui parameters
    m_params.setName("Perlin Noise");
    m_params.add(m_param_offset_x.set("offset x", 5.43, 0.0, 15.0));
    m_params.add(m_param_offset_y.set("offset y", 2.34, 0.0, 15.0));
    m_params.add(m_param_scale.set("scale", 0.0055, 0.001, 0.01));
    m_params.add(m_param_speed.set("speed", 0.5, 0.05, 0.95));
}


void PerlinNoiseFbo::update() {
    // update fbo with result of shader
    // uniform variable are passed to the shader in oder to control the rednering via the gui.
    m_fbo.begin();
    m_shader.begin();
    
    m_shader.setUniform1f("time", ofGetElapsedTimef());
    m_shader.setUniform2f("offset", m_param_offset_x, m_param_offset_y);
    m_shader.setUniform1f("scale", m_param_scale);
    m_shader.setUniform1f("speed", m_param_speed);
    
    ofDrawRectangle(0, 0, m_fbo.getWidth(), m_fbo.getHeight());
    
    m_shader.end();
    m_fbo.end();
    
    m_fbo.getTexture().readToPixels(m_image);
}


void PerlinNoiseFbo::draw() {
    // draw fbo contents to stage
    m_fbo.draw( 0, 0 );
}


ofImage& PerlinNoiseFbo::getImage() {
    return m_image;
}


ofPixels& PerlinNoiseFbo::getPixels() {
    return m_image.getPixels();
}


ofParameterGroup& PerlinNoiseFbo::getParams() {
    return m_params;
}

