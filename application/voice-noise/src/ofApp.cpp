#include "ofApp.h"


void ofApp::setup() {
    
    ofBackground(0);
    ofSetCircleResolution(120);
    
    m_sample_rate = 44100;
    m_buffer_size = 512;
    
    ofLog() << "number of samples: " << m_file_names.size();
    
    m_voices = vector<VoiceSynthesis>(m_file_names.size());
    
    for (unsigned int i = 0; i < m_file_names.size(); ++i) {
        
        ofLog() << (i+1) << ": " << m_file_names[i];
        m_voices[i].setup(m_file_names[i]);
        
    }
    
    maxiSettings::setup(m_sample_rate, 2, m_buffer_size);
    
    ofSoundStreamSetup(2, 0, m_sample_rate, m_buffer_size, 4);
    
}


void ofApp::update() {
    
    vector<VoiceSynthesis>::iterator voice;
    for (voice = m_voices.begin(); voice != m_voices.end(); ++voice) {
        voice->update();
    }
    
}


void ofApp::draw() {
    
    ofDrawBitmapString("FPS: " + to_string((int) ofGetFrameRate()), 10, 21);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    
    ofPushStyle();
    ofSetColor(240, 40, 40, 40);
    
    vector<VoiceSynthesis>::iterator voice;
    for (voice = m_voices.begin(); voice != m_voices.end(); ++voice) {
        float amplitude = voice->getOscillator().getMaxAmplitude() * 2;
        ofDrawEllipse(0, 0, amplitude, amplitude);
    }
    
    for (voice = m_voices.begin(); voice != m_voices.end(); ++voice) {
        ofSetColor(191, 191, 191, 128);
        voice->getOscillator().getMesh().draw();
        
        ofSetColor(191, 191, 191, 255);
        float head_radius = 5.f;
        ofDrawEllipse(voice->getOscillator().getOscillator().getPosition(), head_radius, head_radius);
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}


void ofApp::exit() {
    
    ofSoundStreamClose();
    
}


void ofApp::audioOut(float *output, int buffer_size, int channels) {
    
    double sample;
    vector<VoiceSynthesis>::iterator voice;
    for (unsigned int i = 0; i < buffer_size; ++i) {
        
        sample = 0.0;
        for (voice = m_voices.begin(); voice != m_voices.end(); ++voice) {
            sample += voice->getSample();
        }
        
        output[i * channels] = sample;
        output[i * channels + 1] = sample;
        
    }
    
}


void ofApp::mousePressed(int x, int y, int button) {
    
    unsigned int voice_index = (unsigned int) ofRandom(0, m_voices.size());
    unsigned int num_loops = (unsigned int) ofRandom(1, 5);
    
    m_voices[voice_index].playLoops(num_loops);
    
}

