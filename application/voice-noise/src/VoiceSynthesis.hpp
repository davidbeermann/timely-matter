#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "VoiceOscillator.hpp"

// type definition of window function to easily switch between options.
// https://en.wikipedia.org/wiki/Window_function
// available options in ofxMaxim - see maxiGrains.h for details:
// - hannWinFunctor
// - hammingWinFunctor
// - cosineWinFunctor
// - rectWinFunctor
// - triangleWinFunctor
// - triangleNZWinFunctor
// - blackmanHarrisWinFunctor
// - blackmanNutallWinFunctor
// - gaussianWinFunctor
typedef hannWinFunctor windowFunction;

typedef maxiTimePitchStretch<windowFunction, maxiSample> myGrain;


class VoiceSynthesis {

    maxiSample m_sample;
    myGrain *m_sample_stretcher;
    VoiceOscillator m_osc;
    
    string m_file_name;
    double m_grain_rate, m_grain_length;
    unsigned int m_num_loops, m_loop_count;
    bool m_looping;
    double m_last_position;
    
public:
    void setup(string file_name);
    void update();
    void playLoops(unsigned int num_loops);
    double getSample();
    
    VoiceOscillator& getOscillator() {
        return m_osc;
    }

};