#pragma once

#include "ofMain.h"


class PerlinNoiseFbo {
    
    ofShader m_shader;
    ofFbo m_fbo;
    ofImage m_image;
    
    ofParameterGroup m_params;
    ofParameter<float> m_param_offset_x;
    ofParameter<float> m_param_offset_y;
    ofParameter<float> m_param_scale;
    ofParameter<float> m_param_speed;
    
public:
    void setup(const int& width, const int& height);
    void update();
    void draw();
    
    ofImage& getImage();
    ofPixels& getPixels();
    ofParameterGroup& getParams();
    
};