#pragma once

#include "KinectView.hpp"
#include "ImageSelection.hpp"


class KinectViewCalibration : public KinectView {
    ofImage m_infrarred_image;
    ImageSelection m_selection;
    ofVec2f m_center_position;
protected:
    void m_onWindowResized(const int width, const int height);
    void m_doSetup();
    void m_doUpdate();
    void m_doDraw();
    const ofParameterGroup& m_doGetParams();
};