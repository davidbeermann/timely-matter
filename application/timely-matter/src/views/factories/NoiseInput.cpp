#include "NoiseInput.hpp"

using namespace timelymatter;


void NoiseInput::m_onSetup() {
    // loads vertex and fragment shader named perlin.vert and perlin.frag
    m_shader.load("perlin");
    
    // allocate memory for FBO
    m_fbo.allocate(m_kinect_model.getDepthBufferWidth(), m_kinect_model.getDepthBufferHeight());
    
    // clear FBO contents
    m_fbo.begin();
    ofClear(0);
    m_fbo.end();
    
    // allocate image buffer for pixel access
    m_image.allocate(m_fbo.getWidth(), m_fbo.getHeight(), OF_IMAGE_COLOR_ALPHA);
    
    // setup GUI settings
//    mGuiParams.setName("Perlin Noise");
//    mGuiParams.add(m_offset_x.set("offset x", 5.43, 0.0, 15.0));
//    mGuiParams.add(m_offset_y.set("offset y", 2.34, 0.0, 15.0));
//    mGuiParams.add(m_scale.set("scale", 0.0055, 0.001, 0.01));
//    mGuiParams.add(m_speed.set("speed", 0.5, 0.05, 0.95));
//    mGuiParams.add(m_draw_output.set("draw FBO", true));
}


void NoiseInput::m_onUpdate() {
    // draw shader into FBO
    m_fbo.begin();
    m_shader.begin();
    
    // pass GUI parameters to shader
    m_shader.setUniform1f("time", ofGetElapsedTimef());
    m_shader.setUniform2f("offset", m_offset_x, m_offset_y);
    m_shader.setUniform1f("scale", m_scale);
    m_shader.setUniform1f("speed", m_speed);
    
    // simply draw a rectangle of the FBO's size in order to have any fragments to process
    ofDrawRectangle(0, 0, m_fbo.getWidth(), m_fbo.getHeight());
    
    m_shader.end();
    m_fbo.end();
}


void NoiseInput::m_onDraw() {
    if(m_draw_output) {
        // draw FBO to stage
        m_fbo.draw(0, 0);
    }
}


const ofPixels& NoiseInput::m_onGetPixels() {
    // write FBO pixel data into image buffer
    m_fbo.readToPixels(m_image.getPixels());
    return m_image.getPixels();
}


const unsigned int NoiseInput::m_onGetWidth() {
    return m_fbo.getWidth();
}


const unsigned int NoiseInput::m_onGetHeight() {
    return m_fbo.getHeight();
}


const AppMode NoiseInput::m_onGetType() {
    return AppMode::NOISE;
}


const string NoiseInput::m_onGetName() {
    return "Perlin Noise";
}


