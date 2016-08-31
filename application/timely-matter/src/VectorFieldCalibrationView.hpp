#pragma once

#include "ofMain.h"
#include "KinectView.hpp"
#include "AppModel.hpp"
#include "ViewEvents.hpp"
#include "VectorField.h"


class VectorFieldCalibrationView : public KinectView {
    AppModel& m_model;
    ViewEvents& m_events;
    ofVec2f m_center_position;
    ofRectangle m_fbo_output_size;
    ofFbo m_selection_fbo;
    ofFbo m_output_fbo;
    ofImage m_kinect_image;
    ofImage m_depth_image;
    VectorField m_vector_field;
protected:
    // concrete implementations for AppView
    void m_onWindowResized(const int width, const int height);
    // concrete implementations for KinectView
    void m_doSetup();
    void m_doUpdate();
    void m_doDraw();
    const ofParameterGroup& m_doGetParams();
    
public:
    VectorFieldCalibrationView() : m_model(AppModel::get()), m_events(ViewEvents::get()) {}
};