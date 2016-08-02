#include "ofApp.h"


void ofApp::setup() {
    // load vertex and fragment shaders
    // the vertex shader doesn't really do anything.
    // all the magic is happening in the fragment shader.
    mShader.load("perlin.vert", "perlin.frag");
    
    // initialize off-screen fbo
    mFbo.allocate(FBO_WIDTH, FBO_HEIGHT);
    // clear frame buffer
    mFbo.begin();
    ofClear(0);
    mFbo.end();
    
    // setup gui to control perlin noise parameters
    mGui.setup("Perlin Noise Params");
    mGui.setPosition(10, 10);
    mGui.add(mGuiOffsetX.set("offset x", 5.43, 0.0, 15.0));
    mGui.add(mGuiOffsetY.set("offset y", 2.34, 0.0, 15.0));
    mGui.add(mGuiScale.set("scale", 0.0055, 0.001, 0.01));
    mGui.add(mGuiSpeed.set("speed", 0.5, 0.05, 0.95));
    
    // set initial position in window
    windowResized(ofGetWidth(), ofGetHeight());
}


void ofApp::update() {
    // write frame rate to window title to see how blazing fast rendering is
    ofSetWindowTitle("FPS " + to_string((int) ofGetFrameRate()));
    
    // update fbo with result of shader
    // uniform variable are passed to the shader in oder to control the rednering via the gui.
    mFbo.begin();
    mShader.begin();
    mShader.setUniform1f("time", ofGetElapsedTimef());
    mShader.setUniform2f("offset", mGuiOffsetX, mGuiOffsetY);
    mShader.setUniform1f("scale", mGuiScale);
    mShader.setUniform1f("speed", mGuiSpeed);
    ofDrawRectangle(0, 0, mFbo.getWidth(), mFbo.getHeight());
    mShader.end();
    mFbo.end();
}


void ofApp::draw() {
    // draw fbo contents to stage
    mFbo.draw( mFboPos );
    
    // draw gui at the top of the stage
    mGui.draw();
}


void ofApp::windowResized(int w, int h) {
    mFboPos.x = (w - mFbo.getWidth()) * 0.5f;
    mFboPos.y = (h - mFbo.getHeight()) * 0.5f;
}