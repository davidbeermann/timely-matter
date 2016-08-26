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
    ofRectangle m_bounds;
    float m_handle_radius;
    ofColor m_line_color;
    SelectionHandle m_handle_tl;
    SelectionHandle m_handle_tr;
    SelectionHandle m_handle_br;
    SelectionHandle m_handle_bl;
    vector<SelectionHandle*> m_handles;
public:
    void setup(const ofRectangle bounds);
    void draw();
    const vector<SelectionHandle*>& getHandles() const;
};
