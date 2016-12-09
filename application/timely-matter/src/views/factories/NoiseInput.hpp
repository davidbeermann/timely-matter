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
        ofParameter<bool> m_draw_output;
        
    protected:
        // implementations of abstract class methods
        void m_onWindowResized(const int width, const int height) {};
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
        
        void m_onDraw(const ofRectangle& size);
        const ofPixels& m_onGetPixels();
        const unsigned int m_onGetWidth();
        const unsigned int m_onGetHeight();
        
        ofParameterGroup& m_onGetParams() {
            return m_params;
        }
        const AppMode m_onGetType() {
            return AppMode::NOISE;
        }
        const string m_onGetName() {
            return "Perlin Noise";
        }
    };

}