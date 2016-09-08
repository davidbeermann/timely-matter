#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "RectangularSelection.hpp"


namespace timelymatter {

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
        void setup(const string& image_name);
        void setup(const unsigned int width, const unsigned int height);
        void draw();
        void updatePosition(const ofVec2f& position);
        void enableMask(const bool value);
        void setHandlePositions(const vector<ofVec2f>& positions);
        vector<ofVec2f> getPoints();
        vector<cv::Point2f> getPointsForCv();
        
        
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

}



