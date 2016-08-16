#pragma once

#include "ofMain.h"


class PerlinNoiseFbo {
    ofShader mShader;
    ofFbo mFbo;
    ofImage mImage;
    ofParameterGroup mGuiParams;
    ofParameter<float> mGuiOffsetX;
    ofParameter<float> mGuiOffsetY;
    ofParameter<float> mGuiScale;
    ofParameter<float> mGuiSpeed;
    ofParameter<bool> mGuiDrawOutput;
public:
    void setup(const unsigned int width, const unsigned int height);
    void update();
    void draw();
    const ofParameterGroup& getGuiParams();
    const ofPixels& getPixels();
};
