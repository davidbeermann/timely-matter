#include "Oscillator.hpp"


void SignalGenerator::setup(double phase, double frequency, double amplitude) {
    setup(GeneratorType::BOTH, phase, frequency, amplitude);
}


void SignalGenerator::setup(GeneratorType type, double phase, double frequency, double amplitude) {
    m_type = type;
    m_phase = phase;
    m_frequency = frequency;
    m_amplitude = amplitude;
}


void SignalGenerator::update() {
    m_counter += m_frequency;
    if (m_counter > TWO_PI) {
        m_counter -= TWO_PI;
    }
}


void SignalGenerator::apply(double& sin_value, double& cos_value) {
    if (m_type == GeneratorType::BOTH || m_type == GeneratorType::SIN) {
        sin_value += sin(m_phase + m_counter) * m_amplitude;
    }
    if (m_type == GeneratorType::BOTH || m_type == GeneratorType::COS) {
        cos_value += cos(m_phase + m_counter) * m_amplitude;
    }
}


void Oscillator::update() {
    
    m_position.set(0.0);
    m_sin_value = 0.0;
    m_cos_value = 0.0;
    
    vector<SignalGenerator>::iterator gen;
    for (gen = m_generators.begin(); gen != m_generators.end(); ++gen) {
        gen->update();
        gen->apply(m_sin_value, m_cos_value);
    }
    
    m_position.x = m_cos_value;
    m_position.y = m_sin_value;
    
}


SignalGenerator& Oscillator::addGenerator(SignalGenerator& gen) {
    
    m_generators.push_back(gen);
    return m_generators[m_generators.size()-1];
    
}

