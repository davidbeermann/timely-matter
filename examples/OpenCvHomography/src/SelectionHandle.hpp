#pragma once

#include "ofMain.h"


class SelectionHandle {
    ofRectangle m_bounds;
    ofVec2f m_position, m_click_offset;
    ofColor m_color;
    float m_radius, m_radius_double;
    bool m_is_over, m_is_dragging;
    unsigned int m_alpha_min, m_alpha_max;
    const bool isOverHandle(const ofVec3f& position);
public:
    SelectionHandle() {
        // add mouse event listeners
        ofRegisterMouseEvents(this);
    };
    ~SelectionHandle() {
        // remove mouse event listeners
        ofUnregisterMouseEvents(this);
    };
    void setup(const ofRectangle& bounds, const ofVec2f position, const float radius);
    void draw();
    const ofVec2f& getPosition() const;
    // mouse event listener methods ÐÊmandatory when registering listeners!
    void mouseMoved(ofMouseEventArgs& args);
    void mouseDragged(ofMouseEventArgs& args);
    void mousePressed(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);
    void mouseScrolled(ofMouseEventArgs& args) {};
    void mouseEntered(ofMouseEventArgs& args) {};
    void mouseExited(ofMouseEventArgs& args) {};    
};