#pragma once

#include "ofMain.h"
#include "ofEvents.h"


class SelectionHandle {
    const bool m_isOverHandle(const ofVec3f& position);
    
    ofRectangle m_bounds;
    ofVec2f m_position, m_click_offset;
    ofColor m_color;
    float m_radius, m_radius_double;
    bool m_is_over, m_is_dragging;
    unsigned int m_alpha;
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
    
    void updateBounds(const ofRectangle& bounds);
//    ofVec2f& getPosition() { return m_position; };
    const ofVec2f& getPosition() const { return m_position; };
    
    // mouse event listener methods ÐÊmandatory when registering listeners!
    void mouseMoved(ofMouseEventArgs& args);
    void mouseDragged(ofMouseEventArgs& args);
    void mousePressed(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);
    void mouseScrolled(ofMouseEventArgs& args) {};
    void mouseEntered(ofMouseEventArgs& args) {};
    void mouseExited(ofMouseEventArgs& args) {};
    
    // custom events
    ofEvent<void> onHandleDragStart;
    ofEvent<void> onHandleDragStop;
};