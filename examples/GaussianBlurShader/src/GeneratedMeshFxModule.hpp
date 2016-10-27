#pragma once

#include "ofMain.h"
#include "PostFxModule.hpp"


class GeneratedMeshFxModule : public PostFxModule {
    
    ofFbo m_texture;
    ofVboMesh m_mesh;
    ofShader m_shader;
    ofParameterGroup m_params;
    ofParameter<bool> m_param_enabled;
    ofParameter<bool> m_param_wireframe;
    ofParameter<int> m_param_resolution;
    ofParameter<float> m_param_radius;
    
protected:
    void doInit(unsigned int width, unsigned int height);
    void doRender(ofFbo& input);
    
public:
    ofParameterGroup& getParams() {
        return m_params;
    }

};