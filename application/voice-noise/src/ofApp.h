#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "SoundParams.hpp"
#include "SoundControls.hpp"
#include "VoiceSynthesis.hpp"

//#define OSC_ENABLED


class ofApp : public ofBaseApp {
    
    SoundParams & m_params;
#ifdef OSC_ENABLED
    SoundControls m_controls;
#endif
    
    unsigned int m_sample_rate;
    unsigned int m_buffer_size;
    
    vector<string> m_file_names = {
        "atoms-and-the-void-and-nothing-else-mono.wav",
        "even-in-the-continuity-of-ones-consciousness-mono.wav",
        "matter-does-time-mono.wav",
        "nature-ceaselessly-experiments-mono.wav",
        "nobody-understands-time-mono.wav",
        "space-and-time-are-matters-agential-performances-mono.wav",
        "the-world-makes-us-mono.wav",
        "there-is-perpetual-creation-of-possibility-mono.wav",
        "what-is-real-is-the-process-mono.wav"
    };
    vector<VoiceSynthesis> m_voices;
    
public:
    ofApp() : m_params(SoundParams::get()) {}
    
    void setup();
    void update();
    void draw();
    void exit();
    void audioOut(float *output, int buffer_size, int channels);
    //    void keyPressed(int key);
    //    void keyReleased(int key);
    //    void mouseMoved(int x, int y );
    //    void mouseDragged(int x, int y, int button);
    //    void mousePressed(int x, int y, int button);
    //    void mouseReleased(int x, int y, int button);
    //    void mouseEntered(int x, int y);
    //    void mouseExited(int x, int y);
    //    void windowResized(int w, int h);
    //    void dragEvent(ofDragInfo dragInfo);
    //    void gotMessage(ofMessage msg);
    
    void onPlayRandomSample();
    
};
