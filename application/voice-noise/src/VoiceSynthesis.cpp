#include "VoiceSynthesis.hpp"


void VoiceSynthesis::setup(string file_name) {
    
    m_file_name = file_name;
    
    m_sample.load(ofToDataPath(file_name));
    m_sample_stretcher = new myGrain(&m_sample);
    
    m_osc.setup();
    
    m_looping = false;

}


void VoiceSynthesis::update() {
    
    m_osc.update();
    
    m_grain_rate = ofMap(m_osc.getOscillator().getCosValue(), -m_osc.getMaxAmplitude(), m_osc.getMaxAmplitude(), -1.5, 1.5);
    m_grain_length = ofMap(m_osc.getOscillator().getSinValue(), -m_osc.getMaxAmplitude(), m_osc.getMaxAmplitude(), 0.09, 0.015);
    
}


void VoiceSynthesis::playLoops(unsigned int num_loops) {
    
    ofLog() << "play " << num_loops << " loops (" << m_file_name << ")";

    if (!m_looping) {
        m_num_loops = num_loops;
        m_loop_count = 0;
        m_sample.setPosition(0.0);
        m_last_position = 0.0;
        m_looping = true;
    } else {
        ofLog() << "sample already looping... (" << m_file_name << ")";
    }
    
}


double VoiceSynthesis::getSample() {
    
    if (m_looping) {
        if (m_sample.getPosition() < m_last_position) {
            m_last_position = 0.0;
            ++m_loop_count;
//            ofLog() << m_loop_count << " of " << m_num_loops << " loops finished (" << m_file_name << ")";
            if (m_loop_count == m_num_loops) {
                ofLog() << "loops complete! (" << m_file_name << ")";
                m_looping = false;
            }
        } else {
            m_last_position = m_sample.getPosition();
        }
    }

    if (m_looping) {
        return m_sample.play() * 1.15;
    } else {
        return m_sample_stretcher->play(1., m_grain_rate, m_grain_length, 4, 0) * 0.25;
    }

}

