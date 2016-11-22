#pragma once

#include "ofMain.h"
#include "Oscillator.hpp"


class VoiceOscillator {

    Oscillator m_oscillator;
    ofMesh m_mesh;
    float m_max_amplitude;
    
    void addGenerator(GeneratorType type, float max_amplitude);
    GeneratorType getGeneratorType();
    
public:
    void setup();
    void update();
    
    Oscillator& getOscillator() {
        return m_oscillator;
    }
    ofMesh& getMesh() {
        return m_mesh;
    }
    const float& getMaxAmplitude() const {
        return m_max_amplitude;
    }
    
};