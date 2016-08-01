#include "ofApp.h"


void ofApp::setup() {
    // lower frame rate to see console output
    ofSetFrameRate(1);
    ofSetBackgroundColor(0);
    
    // allocate memory for image
    mImage.allocate(600, 200, OF_IMAGE_COLOR_ALPHA);
    ofLog() << "image type: " << mImage.getPixels().getImageType() << " - num channels: " << mImage.getPixels().getNumChannels();
}


void ofApp::update() {
    // update random pixel position
    mPixelPosition.set((int) ofRandom(mImage.getWidth()), (int) ofRandom(mImage.getHeight()));
    ofLog() << "- - - - - - - - - -";
    ofLog() << "pixel position: " << mPixelPosition;
    
    // generate random RGB color components
    int r = (int) ofRandom(255);
    int g = (int) ofRandom(255);
    int b = (int) ofRandom(255);
    int a = 255;
    ofLog() << "image RGBA: " << r << " " << g << " " << b << " " << a;
    
    // set color at generated position
    mImage.setColor(mPixelPosition.x, mPixelPosition.y, ofColor(r,g,b,a));
    // update the image so changes to it are visible when drawn to stage
    mImage.update();
    
    // calculate center postion for image
    mImagePosition.set((int)((ofGetWidth() - mImage.getWidth()) * 0.5f), (int)((ofGetHeight() - mImage.getHeight()) * 0.5f));
}


void ofApp::draw() {
    // get reference to pixels array
    const ofPixels &pixels = mImage.getPixels();
    
    // the color components are stored in the pixels array per row with a single value per channel.
    // therefore the index of the first channel is calculated (ypos * imagewidth + xpos) * numchannels.
    // the other channels are accessed in consecutive order after the starting index.
    // the channel values are stored in a char array which are converted back into int values by writing to value
    // a variable of type int. alternatively one could do a static_cast.
    int index = (mPixelPosition.y * mImage.getWidth() + mPixelPosition.x) * pixels.getNumChannels();
    int r = pixels[index]; //static_cast<int>(pixels[index]);
    int g = pixels[index + 1]; //static_cast<int>(pixels[index + 1]);
    int b = pixels[index + 2]; //static_cast<int>(pixels[index + 2]);
    int a = pixels[index + 3]; //static_cast<int>(pixels[index + 3]);
    ofLog() << "pixel RGBA: " << r << " " << g << " " << b << " " << a;
    
    // draw altered image to stage
    mImage.draw(mImagePosition);
}
