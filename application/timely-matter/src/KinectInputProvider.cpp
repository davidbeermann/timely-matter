#include "KinectInputProvider.h"
#include "KinectHomographyCalibration.hpp"
#include "ViewEvents.hpp"


KinectInputProvider::~KinectInputProvider() {
//    ofLog() << "~KinectInputProvider()";
    m_kinect.close();
}


void KinectInputProvider::storeHomographyPoints() {
    ofLog() << "KinectInputProvider::storeHomographyPoints()";
    
    KinectHomographyCalibration* concreteView = static_cast<KinectHomographyCalibration*>(m_view);
    vector<cv::Point2f> points = concreteView->getHomographyPoints();
    ofLog() << "number of points: " << points.size();
}


void KinectInputProvider::doSetup() {
    // Kinect method signature: init(bool infrared, bool video, bool texture)
    // enable Kinect with infrared video and texture
    m_kinect.init(true, true, true);
    
    // uses some cpu - scews the video image?!
    //m_kinect.setRegistration(true);
    
    // setup GUI to control Kinect
    mGuiParams.setName("Kinect");
    mGuiParams.add(mGuiShowDepthImage.set("show depth image", true));
    mGuiParams.add(mGuiDepthNearPlane.set("depth near plane", 500, 500, 1000));
    mGuiParams.add(mGuiDepthFarPlane.set("depth far plane", 1500, 1000, 2500));
    
    // open connection to Kinect and start grabbing images
    m_kinect.open();
    
    m_view = new KinectHomographyCalibration();
    m_view->setup(&m_kinect);
    
    ofAddListener(ViewEvents::get().onHomographySelected, this, &KinectInputProvider::storeHomographyPoints);
}


void KinectInputProvider::doUpdate() {
    // set depth clipping
    // the closer the range the better results for the texture gray values between 0-255.
    m_kinect.setDepthClipping(mGuiDepthNearPlane, mGuiDepthFarPlane);
    
    // update Kinect - grab new camera data
    m_kinect.update();
    
    m_view->update();
}


void KinectInputProvider::doDraw() {
    // draw texture to stage
    if (mGuiShowDepthImage) {
        m_kinect.drawDepth(0, 0);
    }
    
    m_view->draw();
}


const ofPixels& KinectInputProvider::doGetPixels() {
    return m_kinect.getDepthPixels();
}


const unsigned int KinectInputProvider::doGetWidth() {
    return (unsigned int) m_kinect.getWidth();
}


const unsigned int KinectInputProvider::doGetHeight() {
    return (unsigned int) m_kinect.getHeight();
}


const AppMode KinectInputProvider::doGetType() {
    return AppMode::KINECT;
}


const string KinectInputProvider::doGetName() {
    return "Kinect";
}


const bool KinectInputProvider::doIsReady() {
    return false;
}


void KinectInputProvider::m_doAddParams(AppUI& ui) {
    ui.addParameters(mGuiParams);
    if (m_view != nullptr) {
        ui.addParameters(m_view->getParams());
    }
}

