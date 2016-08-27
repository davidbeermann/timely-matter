#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "AppVars.hpp"
#include "VectorFieldInputFactory.h"
#include "VectorFieldInputProvider.h"
#include "VectorField.h"
#include "ParticleSystem.h"


class ofApp : public ofBaseApp {
    VectorFieldInputFactory m_input_factory;
    VectorFieldInputProvider* m_input_provider;
    VectorField m_vector_field;
    ParticleSystem m_particle_system;
    bool m_update_window_size;
    
    ofVec2f mCenteredPos;
public:
    void setup();
    void update();
    void draw();
    void windowResized(int w, int h);
    
    const bool isInputAvailable();
    void setInputProvider(const AppMode mode);
    
    const ofParameterGroup& getInputParams() { return m_input_provider->getGuiParams(); };
    const ofParameterGroup& getVectorFieldParams() { return m_vector_field.getGuiParams(); };
    const ofParameterGroup& getParticleSystemParams() { return m_particle_system.getGuiParams(); };
};
