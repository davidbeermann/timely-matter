#pragma once

#include "ofMain.h"
#include "KinectView.hpp"
#include "AppModel.hpp"
#include "ViewEvents.hpp"
#include "VectorField.h"
#include "ParticleSystem.h"


class KinectRenderView : public KinectView {
    AppModel& m_model;
    ViewEvents& m_events;
    // view attributes
    ofVec2f m_center_position;
    ofImage m_full_depth_image;
    ofImage m_crop_depth_image;
    VectorField m_vector_field;
    ParticleSystem m_particle_system;
    // gui attributes
    ofParameterGroup m_params;
protected:
    // app view implementations
    void m_onWindowResized(const int width, const int height);
    // kinect view implementations
    void m_doSetup();
    void m_doUpdate();
    void m_doDraw();
    const ofParameterGroup& m_doGetParams();
public:
    KinectRenderView() : m_model(AppModel::get()), m_events(ViewEvents::get()) {};
    ~KinectRenderView() {};
};