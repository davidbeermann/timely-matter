#include "ofApp.h"


void ofApp::setup() {
    // load vertex and fragment shaders
    mShader.load("perlin.vert", "perlin.frag");
    
    // initialize off-screen fbo
    mFbo.allocate(FBO_WIDTH, FBO_HEIGHT);
    
    // clear fbo
    mFbo.begin();
    ofClear(0);
    mFbo.end();
    
    // initialize image to read values from fbo into
    mImage.allocate(FBO_WIDTH, FBO_HEIGHT, OF_IMAGE_COLOR_ALPHA);
    
    // init vector field
    mVectorField.setup(FBO_WIDTH, FBO_HEIGHT, FIELD_SUBDIVISION);
    
    // setup gui to control perlin noise parameters
    mGui.setup("Parameters");
    mGui.setPosition(10, 10);
    // perlin noise parameters
    mPerlinNoise.setName("Perlin Noise");
    mPerlinNoise.add(mPerlinOffsetX.set("offset x", 5.43, 0.0, 15.0));
    mPerlinNoise.add(mPerlinOffsetY.set("offset y", 2.34, 0.0, 15.0));
    mPerlinNoise.add(mPerlinScale.set("scale", 0.0055, 0.001, 0.01));
    mPerlinNoise.add(mPerlinSpeed.set("speed", 0.5, 0.05, 0.95));
    mGui.add(mPerlinNoise);
    // vector field parameters
    mGui.add(mVectorField.getGuiParams());
    
    // initialize fbo position
    windowResized(ofGetWidth(), ofGetHeight());
}


void ofApp::update() {
    // write frame rate to window title
    ofSetWindowTitle("FPS " + to_string((int) ofGetFrameRate()));
    
    // update fbo with result of shader
    // uniform variable are passed to the shader in oder to control the rednering via the gui.
    mFbo.begin();
    mShader.begin();
    mShader.setUniform1f("time", ofGetElapsedTimef());
    mShader.setUniform2f("offset", mPerlinOffsetX, mPerlinOffsetY);
    mShader.setUniform1f("scale", mPerlinScale);
    mShader.setUniform1f("speed", mPerlinSpeed);
    ofDrawRectangle(0, 0, mFbo.getWidth(), mFbo.getHeight());
    mShader.end();
    mFbo.end();
    
    // read pixel data from GPU to RAM
    // this seems to automatically convert any image to ofImageType 2: RGBA – possibly to vec4 output of shader.
    // whereby each color takes up four chars – one per channel – in the pixels array!
    mFbo.readToPixels(mImage.getPixels());
    
    // update the image!!!
    // changed pixel data will be available for updates.
    // But otherwise the changed pixels will not be drawn to the stage.
    mImage.update();
    
    // pass pixels to vector field
    mVectorField.update(mImage.getPixels(), 32.f);
}


void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(mFboPos);
    
    // draw perlin noise image
    mImage.draw(0,0);
    
    // draw vector field info
    mVectorField.draw();
    
    ofPopMatrix();
    
    if (mShowGui) {
        mGui.draw();
    }
}


void ofApp::keyReleased(int key) {
    if(key == 'g') {
        mShowGui = !mShowGui;
    }
}


void ofApp::windowResized(int w, int h) {
    mFboPos.x = (w - mFbo.getWidth()) * 0.5f;
    mFboPos.y = (h - mFbo.getHeight()) * 0.5f;
}

