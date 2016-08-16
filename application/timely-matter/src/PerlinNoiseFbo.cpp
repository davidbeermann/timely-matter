#include "PerlinNoiseFbo.h"


void PerlinNoiseFbo::setup(const unsigned int width, const unsigned int height) {
    // loads vertex and fragment shader named perlin.vert and perlin.frag
    mShader.load("perlin");
    
    // allocate memory for FBO
    mFbo.allocate(width, height);
    
    // clear FBO contents
    mFbo.begin();
    ofClear(0);
    mFbo.end();
    
    // allocate image buffer for pixel access
    mImage.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    
    // setup GUI settings
    mGuiParams.setName("Perlin Noise Params");
    mGuiParams.add(mGuiOffsetX.set("offset x", 5.43, 0.0, 15.0));
    mGuiParams.add(mGuiOffsetY.set("offset y", 2.34, 0.0, 15.0));
    mGuiParams.add(mGuiScale.set("scale", 0.0055, 0.001, 0.01));
    mGuiParams.add(mGuiSpeed.set("speed", 0.5, 0.05, 0.95));
    mGuiParams.add(mGuiDrawOutput.set("draw FBO", true));
}


void PerlinNoiseFbo::update() {
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


void PerlinNoiseFbo::draw() {
    // draw FBO to stage
    if(mGuiDrawOutput) {
        mFbo.draw(0, 0);
    }
}


const ofParameterGroup& PerlinNoiseFbo::getGuiParams() {
    return mGuiParams;
}


const ofPixels& PerlinNoiseFbo::getPixels() {
    // write FBO pixel data into image buffer
    mFbo.readToPixels(mImage.getPixels());
    return mImage.getPixels();
}