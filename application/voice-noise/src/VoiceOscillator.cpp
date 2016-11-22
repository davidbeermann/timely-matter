#include "VoiceOscillator.hpp"


void VoiceOscillator::addGenerator(GeneratorType type, float max_amplitude) {
    
//    switch (type) {
//        case GeneratorType::BOTH:
//            ofLog() << "addGenerator() BOTH";
//            break;
//        case GeneratorType::SIN:
//            ofLog() << "addGenerator() SIN";
//            break;
//        case GeneratorType::COS:
//            ofLog() << "addGenerator() COS";
//            break;
//    }

    // 1Hz => TWO_PI/60.0 = 0.104719755
    double minHz = TWO_PI / 480.0; // 0.125Hz
    double maxHz = TWO_PI / 240.0; // 0.25Hz
    
    SignalGenerator gen;
    float amplitude = ofRandom(max_amplitude * 0.25f, max_amplitude);
    gen.setup(type, ofRandom(TWO_PI), ofRandom(minHz, maxHz), amplitude);
    m_oscillator.addGenerator(gen);
    m_max_amplitude += amplitude;
    
}


GeneratorType VoiceOscillator::getGeneratorType() {
    
    uint8_t id = (uint8_t) ofRandom(1, 4);
    return GeneratorType(id);

}


void VoiceOscillator::setup() {

    m_max_amplitude = 0;
    
    int num_generators = (int) ofRandom(3, 7);
    float max_amplitude = ((float) ofGetHeight() / 2.f - 20.f) / (float) num_generators;
    
    GeneratorType last_type, type;
    for (int i = 0; i < num_generators; ++i) {
        
        while (type == last_type) {
            uint8_t id = (uint8_t) ofRandom(1, 4);
            type = GeneratorType(id);
        }
        
        addGenerator(type, max_amplitude);
        last_type = type;
        
    }
    
    m_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);

}


void VoiceOscillator::update() {
    
    m_oscillator.update();
    
    m_mesh.addVertex(ofVec3f(m_oscillator.getCosValue(), m_oscillator.getSinValue(), 0.f));
    if (m_mesh.getVertices().size() > 200) {
        m_mesh.removeVertex(0);
    }
    
}
