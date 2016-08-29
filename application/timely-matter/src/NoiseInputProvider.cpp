#include "NoiseInputProvider.h"


void NoiseInputProvider::doSetup() {
    // loads vertex and fragment shader named perlin.vert and perlin.frag
    mShader.load("perlin");
    
    // allocate memory for FBO
    mFbo.allocate(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    // clear FBO contents
    mFbo.begin();
    ofClear(0);
    mFbo.end();
    
    // allocate image buffer for pixel access
    mImage.allocate(mFbo.getWidth(), mFbo.getHeight(), OF_IMAGE_COLOR_ALPHA);
    
    // setup GUI settings
    mGuiParams.setName("Perlin Noise");
    mGuiParams.add(mGuiOffsetX.set("offset x", 5.43, 0.0, 15.0));
    mGuiParams.add(mGuiOffsetY.set("offset y", 2.34, 0.0, 15.0));
    mGuiParams.add(mGuiScale.set("scale", 0.0055, 0.001, 0.01));
    mGuiParams.add(mGuiSpeed.set("speed", 0.5, 0.05, 0.95));
    mGuiParams.add(mGuiDrawOutput.set("draw FBO", true));
}


void NoiseInputProvider::doUpdate() {
    // draw shader into FBO
    mFbo.begin();
    mShader.begin();
    
    // pass GUI parameters to shader
    mShader.setUniform1f("time", ofGetElapsedTimef());
    mShader.setUniform2f("offset", mGuiOffsetX, mGuiOffsetY);
    mShader.setUniform1f("scale", mGuiScale);
    mShader.setUniform1f("speed", mGuiSpeed);
    
    // simply draw a rectangle of the FBO's size in order to have any fragments to process
    ofDrawRectangle(0, 0, mFbo.getWidth(), mFbo.getHeight());
    
    mShader.end();
    mFbo.end();
}


void NoiseInputProvider::doDraw() {
    if(mGuiDrawOutput) {
        // draw FBO to stage
        mFbo.draw(0, 0);
    }
}


const ofPixels& NoiseInputProvider::doGetPixels() {
    // write FBO pixel data into image buffer
    mFbo.readToPixels(mImage.getPixels());
    return mImage.getPixels();
}


const unsigned int NoiseInputProvider::doGetWidth() {
    return mFbo.getWidth();
}


const unsigned int NoiseInputProvider::doGetHeight() {
    return mFbo.getHeight();
}


const AppMode NoiseInputProvider::doGetType() {
    return AppMode::NOISE;
}


const string NoiseInputProvider::doGetName() {
    return "Perlin Noise";
}


const bool NoiseInputProvider::doIsReady() {
    return true;
}


void NoiseInputProvider::m_doAddParams(AppUI& ui) {
    ui.addParameters(mGuiParams);
}


