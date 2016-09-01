#include "KinectInputProvider.h"
#include "KinectCalibrationView.hpp"
#include "VectorFieldCalibrationView.hpp"
#include "KinectRenderView.hpp"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;


KinectInputProvider::~KinectInputProvider() {
//    ofLog() << "~KinectInputProvider()";
    
    m_clearView();

    m_kinect.close();
}


void KinectInputProvider::storeKinectCalibration() {
//    ofLog() << "KinectInputProvider::storeKinectCalibration()";
    
    // remove listener
    ofRemoveListener(m_events.onKinectCalibrated, this, &KinectInputProvider::storeKinectCalibration);
    
    // static cast to concrete view pointer
    KinectCalibrationView* concrete_view = static_cast<KinectCalibrationView*>(m_view);
    m_model.setSelectionPoints(concrete_view->getSelectionPoints());
    m_model.setHomographyMatrix(concrete_view->getHomographyMatrix());
    
    // clear view
    m_clearView();
    
    // create new view
    m_view = new VectorFieldCalibrationView();
    m_view->setup(&m_kinect);
    
    ofAddListener(m_events.onVectorFieldCalibrated, this, &KinectInputProvider::storeVectorFieldCalibration);
}


void KinectInputProvider::storeVectorFieldCalibration() {
    ofRemoveListener(m_events.onVectorFieldCalibrated, this, &KinectInputProvider::storeVectorFieldCalibration);
    
    // static cast to concrete view pointer
    VectorFieldCalibrationView* concrete_view = static_cast<VectorFieldCalibrationView*>(m_view);
    m_model.setDepthFieldOfView(concrete_view->getDepthNearParam(), concrete_view->getDepthFarParam());
    m_model.setFieldForces(concrete_view->getForceFieldParam(), concrete_view->getForceEdgeParam());
    
    m_clearView();
    
    // create new view
    m_view = new KinectRenderView();
    m_view->setup(&m_kinect);
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
    ofAddListener(m_events.onKinectCalibrated, this, &KinectInputProvider::storeKinectCalibration);
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

