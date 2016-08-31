#include "KinectInputProvider.h"
#include "KinectCalibrationView.hpp"
#include "VectorFieldCalibrationView.hpp"
#include "ViewEvents.hpp"
#include "AppModel.hpp"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;


KinectInputProvider::~KinectInputProvider() {
//    ofLog() << "~KinectInputProvider()";
    
    m_clearView();

    m_kinect.close();
}


void KinectInputProvider::storeCalibration() {
//    ofLog() << "KinectInputProvider::storeCalibration()";
    
    // remove listener
    ofRemoveListener(ViewEvents::get().onKinectCalibrated, this, &KinectInputProvider::storeCalibration);
    
    // static cast to concrete view pointer
    KinectCalibrationView* concrete_view = static_cast<KinectCalibrationView*>(m_view);
    AppModel::get().setSelectionPoints(concrete_view->getSelectionPoints());
    AppModel::get().setHomographyMatrix(concrete_view->getHomographyMatrix());
    
    // clear view
    m_clearView();
    
    // create new view
    m_view = new VectorFieldCalibrationView();
    m_view->setup(&m_kinect);
    
    //TODO add listener to view event
}


void KinectInputProvider::doSetup() {
    // Kinect method signature: init(bool infrared, bool video, bool texture)
    // enable Kinect with infrared video and texture
    m_kinect.init(true, true, true);
    
    // uses some cpu - scews the video image?!
    //m_kinect.setRegistration(true);
    
    // open connection to Kinect and start grabbing images
    m_kinect.open();
    
    // create initial view
    m_view = new KinectCalibrationView();
//    m_view = new VectorFieldCalibrationView();
    m_view->setup(&m_kinect);
    
    // add initial view listeners
    ofAddListener(ViewEvents::get().onKinectCalibrated, this, &KinectInputProvider::storeCalibration);
}


void KinectInputProvider::doUpdate() {
    // update Kinect - grab new camera data
    m_kinect.update();
    
    // update view
    if (m_view != nullptr) {
        m_view->update();
    }
}


void KinectInputProvider::doDraw() {
    // update view
    if (m_view != nullptr) {
        m_view->draw();
    }
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
    if (m_view != nullptr) {
        ui.addParameters(m_view->getParams());
    }
}


void KinectInputProvider::m_clearView() {
    if (m_view != nullptr) {
        delete m_view;
        m_view = nullptr;
    }
}

