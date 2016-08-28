#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "SelectionHandle.hpp"


enum class SelectionMode : uint8_t {
    RECT_FIXED = 0,
    RECT_FREEFORM = 1,
    RECT_PROPORTIONAL = 2
};


class RectangularSelection {
    SelectionHandle m_handle_tl, m_handle_tr, m_handle_br, m_handle_bl;
    vector<SelectionHandle*> m_handles;
    ofRectangle m_bounds;
    float m_handle_radius;
    ofColor m_line_color;
    
public:
    void setup(const ofRectangle bounds);
    void draw();
    vector<SelectionHandle*>& getHandles();
};
