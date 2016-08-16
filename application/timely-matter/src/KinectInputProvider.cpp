#include "KinectInputProvider.h"


void KinectInputProvider::doSetup() {
    // Kinect method signature: init(bool infrared, bool video, bool texture)
    // enable Kinect eith infrared video and texture
    mKinect.init(false, false, true);
    
    // uses some cpu - scews the video image?!
    //mKinect.setRegistration(true);
    
    // setup GUI to control Kinect
    mGuiParams.setName("Kinect");
    mGuiParams.add(mGuiShowDepthImage.set("show depth image", true));
    mGuiParams.add(mGuiDepthNearPlane.set("depth near plane", 500, 500, 1000));
    mGuiParams.add(mGuiDepthFarPlane.set("depth far plane", 1500, 1000, 2500));
    
    // open connection to Kinect and start grabbing images
    mKinect.open();
}


void KinectInputProvider::doUpdate() {
    // set depth clipping
    // the closer the range the better results for the texture gray values between 0-255.
    mKinect.setDepthClipping(mGuiDepthNearPlane, mGuiDepthFarPlane);
    
    // update Kinect - grab new camera data
    mKinect.update();
}


void KinectInputProvider::doDraw() {
    // draw texture to stage
    if (mGuiShowDepthImage) {
        mKinect.drawDepth(0, 0);
    }
}


const ofPixels& KinectInputProvider::doGetPixels() {
    return mKinect.getDepthPixels();
}

