#pragma once

#include "ofMain.h"
#include "PostFxModule.hpp"
#include "PingPongFbo.hpp"


class GaussianBlurFxModule : public PostFxModule {

    PingPongFbo m_ping_pong_fbo;
    ofShader m_shader;
    
    ofParameterGroup m_params;
    ofParameter<bool> m_param_enabled;
    ofParameter<int> m_param_strength;
    
protected:
    void doInit(unsigned int width, unsigned int height);
    void doRender(ofFbo& input);
    
public:
    ofParameterGroup& getParams() {
        return m_params;
    }

};