#pragma once

#include "ofMain.h"
#include "AppVars.hpp"
#include "AppUI.hpp"

// Implementation for NVI Non-Virtual Interface derived from here:
// http://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11#answer-14324500

class VectorFieldInputProvider {
private:
    virtual void doSetup() = 0;
    virtual void doUpdate() = 0;
    virtual void doDraw() = 0;
    virtual const ofPixels& doGetPixels() = 0;
    virtual const unsigned int doGetWidth() = 0;
    virtual const unsigned int doGetHeight() = 0;
    virtual const AppMode doGetType() = 0;
    virtual const string doGetName() = 0;
    virtual const bool doIsReady() = 0;
    virtual void m_doAddParams(AppUI& ui) = 0;
protected:
    const unsigned int DEFAULT_WIDTH = 640;
    const unsigned int DEFAULT_HEIGHT = 480;
    ofParameterGroup mGuiParams;
public:
    // enable deletion of a Derived* through a Base*
    virtual ~VectorFieldInputProvider() = default;
    void setup() { doSetup(); };
    void update() { doUpdate(); };
    void draw() { doDraw(); };
    const ofParameterGroup& getGuiParams() { return mGuiParams; };
    const ofPixels& getPixels() { return doGetPixels(); };
    const unsigned int getWidth() { return doGetWidth(); };
    const unsigned int getHeight() { return doGetHeight(); };
    const AppMode getType() { return doGetType(); };
    const string getName() { return doGetName(); };
    const bool isReady() { return doIsReady(); };
    
    void addParams(AppUI& ui){ m_doAddParams(ui); };
};