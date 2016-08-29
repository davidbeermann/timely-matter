#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "RectangularSelection.hpp"


class ImageSelection {
    void m_enableMaskRedraw();
    void m_disableMaskRedraw();
    void m_setup();
    void m_setupMask();
    void m_clearMask();
    void m_drawMask();
    ofVec2f m_position;
    ofRectangle m_bounds;
    ofImage m_image;
    ofFbo m_mask;
    RectangularSelection m_selection;
    bool m_mask_enabled = false, m_redraw_mask = false;
public:
    void setup(const ofVec2f& position, const string& image_name);
    void setup(const ofVec2f& position, const unsigned int width, const unsigned int height);
    void update(const ofVec2f& position);
    void draw();
    const vector<cv::Point2f> getPoints();
    void enableMask(const bool value);
    
    const ofVec2f& getPosition() {
        return m_position;
    };
    
    ofImage& getImage() {
        return m_image;
    };
    
    const unsigned int getWidth() {
        return m_image.getWidth();
    };
    
    const unsigned int getHeight() {
        return m_image.getHeight();
    };
};
