#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "AppUI.hpp"
#include "AppVars.hpp"
#include "VectorFieldInputFactory.h"
#include "VectorFieldInputProvider.h"
#include "VectorField.h"
#include "ParticleSystem.h"


class ofApp : public ofBaseApp {
    void m_prepare_for_rendering();
    
    AppUI m_ui;
    VectorFieldInputFactory m_input_factory;
    VectorFieldInputProvider* m_input_provider;
    VectorField m_vector_field;
    ParticleSystem m_particle_system;
    bool m_is_prepared;
    
    ofVec2f mCenteredPos;
public:
    void setup();
    void update();
    void draw();
    void windowResized(int w, int h);
    
    void updateGuiParameters();
    
    const bool isInputAvailable();
    void setInputProvider(AppMode& mode);
};
