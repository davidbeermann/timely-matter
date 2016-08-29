#pragma once

#include "ofMain.h"
#include "VectorFieldInputProvider.h"
#include "AppVars.hpp"
#include "AppUI.hpp"


class NoiseInputProvider : public VectorFieldInputProvider {
    // implementations of abstract class methods
    void doSetup();
    void doUpdate();
    void doDraw();
    const ofPixels& doGetPixels();
    const unsigned int doGetWidth();
    const unsigned int doGetHeight();
    const AppMode doGetType();
    const string doGetName();
    const bool doIsReady();
    void m_doAddParams(AppUI& ui);
    // private class attributes
    ofShader mShader;
    ofFbo mFbo;
    ofImage mImage;
    ofParameter<float> mGuiOffsetX;
    ofParameter<float> mGuiOffsetY;
    ofParameter<float> mGuiScale;
    ofParameter<float> mGuiSpeed;
    ofParameter<bool> mGuiDrawOutput;
};
