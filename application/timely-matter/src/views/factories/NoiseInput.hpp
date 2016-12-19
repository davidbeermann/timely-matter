#pragma once

#include "ofMain.h"
#include "VectorFieldInput.hpp"
#include "AppMode.hpp"


namespace timelymatter {
    
    class NoiseInput : public VectorFieldInput {
        
        // private class attributes
        ofShader m_shader;
        ofFbo m_fbo;
        ofImage m_image;
        ofParameterGroup m_params;
        ofParameter<bool> m_enabled;
        ofParameter<float> m_offset_x;
        ofParameter<float> m_offset_y;
        ofParameter<float> m_scale;
        ofParameter<float> m_speed;
        
    protected:
        // implementations of abstract class methods
        void m_onWindowResized(const int width, const int height) {};
        void m_onSetup();
        void m_onUpdate();
        
        // the draw methods are not needed for this class
        void m_onDraw() {}
        void m_onDraw(const ofRectangle& size) {}
        
        const ofPixels& m_onGetPixels() {
            // write FBO pixel data into image buffer
            m_fbo.readToPixels(m_image.getPixels());
            return m_image.getPixels();
        }
        const unsigned int m_onGetWidth() {
            return m_fbo.getWidth();
        }
        const unsigned int m_onGetHeight() {
            return m_fbo.getHeight();
        }
        ofParameterGroup& m_onGetParams() {
            return m_params;
        }
        const AppMode m_onGetType() {
            return AppMode::NOISE;
        }
        const string m_onGetName() {
            return "Perlin Noise";
        }
        ofFbo & m_onGetOutputFbo() {
            return m_fbo;
        };
        
    public:
        NoiseInput() {}
        ~NoiseInput() {}
    };

}