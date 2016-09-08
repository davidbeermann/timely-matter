#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "SelectionHandle.hpp"


namespace timelymatter {

    class RectangularSelection {
        SelectionHandle m_handle_tl, m_handle_tr, m_handle_br, m_handle_bl;
        vector<SelectionHandle*> m_handles;
        ofRectangle m_bounds;
        float m_handle_radius;
        ofColor m_line_color;
        
    public:
        void setup(const ofRectangle& bounds);
        void draw();
        void updateBounds(const ofRectangle& bounds);
        void updatePositions(const vector<ofVec2f>& positions);
        vector<SelectionHandle*>& getHandles();
    };

}

