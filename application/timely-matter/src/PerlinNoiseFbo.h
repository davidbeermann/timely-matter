#pragma once

#include "ofMain.h"

class PerlinNoiseFbo {
    ofShader mShader;
    ofFbo mFbo;
    ofParameterGroup mGuiParams;
    ofParameter<float> mGuiOffsetX;
    ofParameter<float> mGuiOffsetY;
    ofParameter<float> mGuiScale;
    ofParameter<float> mGuiSpeed;
public:
    void setup(const unsigned int width, const unsigned int height);
    void update();
    void draw();
    const ofParameterGroup& getGuiParams();
};
