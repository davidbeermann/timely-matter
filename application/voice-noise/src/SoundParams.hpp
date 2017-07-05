#pragma once

#include "ofMain.h"


// Singleton class
// Proposed implementation adapted from here:
// http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
class SoundParams {
    
    // available parameters
    ofParameter<bool> m_playing;
    ofParameter<float> m_volume;
    
    bool m_random;
    
    // private constructor
    SoundParams() {
        m_playing.set("start", true);
        m_volume.set("volume", 1.0f, 0.f, 1.f);
        
        m_random = false;
    }
    
public:
    // static method to retrieve singleton instance
    static SoundParams& get() {
        static SoundParams instance;
        return instance;
    }
    
    // remove copy constructor and and copy assingnment operator - C++ 11 style
    SoundParams(SoundParams const&) = delete;
    void operator=(SoundParams const&) = delete;
    
    // parameter access
    ofParameter<float> & getVolume() {
        return m_volume;
    }
    ofParameter<bool> & getPlaying() {
        return m_playing;
    }
    
    void triggerRandom(bool const value) {
        if (m_random != value) {
            if (value) {
                ofNotifyEvent(play_random_sample, this);
            }
            m_random = value;
        }
    }
    
    ofEvent<void> play_random_sample;

};
