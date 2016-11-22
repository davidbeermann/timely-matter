#pragma once

#include "ofMain.h"


enum class GeneratorType : uint8_t {
    BOTH = 1,
    SIN = 2,
    COS = 3
};


class SignalGenerator {
    
    GeneratorType m_type;
    double m_phase;
    double m_frequency;
    double m_amplitude;
    double m_counter;
    
public:
    void setup(GeneratorType type, double phase, double frequency, double amplitude);
    void setup(double phase, double frequency, double amplitude);
    void update();
    void apply(double& sin_value, double& cos_value);
    
};


class Oscillator {

    vector<SignalGenerator> m_generators;
    double m_sin_value;
    double m_cos_value;
    ofPoint m_position;
    
public:
    SignalGenerator& addGenerator(SignalGenerator& gen);
    void update();
    
    const double& getSinValue() const {
        return m_sin_value;
    }
    const double& getCosValue() const {
        return m_cos_value;
    }
    const double& getX() const {
        return m_cos_value;
    }
    const double& getY() const {
        return m_sin_value;
    }
    const ofPoint& getPosition() const {
        return m_position;
    }
    
};