#include "SelectionHandle.hpp"


void SelectionHandle::setup(const ofRectangle& bounds, const ofVec2f position, const float radius) {
    m_bounds = bounds;
    m_position = position;
    m_radius = radius;
    m_radius_double = radius * 2.f;
    m_color.set(255, 0, 0);
    m_alpha = 51;
    
    m_is_dragging = false;
}


void SelectionHandle::draw() {
    ofPushStyle();
    ofSetColor(m_color, m_alpha);
    
    ofPushMatrix();
    ofTranslate(m_position);
    
    if (m_is_over && !m_is_dragging) {
        ofDrawCircle(0, 0, m_radius);
    }
    
    ofPopMatrix();
    ofPopStyle();
}


const ofVec2f& SelectionHandle::getPosition() const {
    return m_position;
}


void SelectionHandle::mouseMoved(ofMouseEventArgs& args) {
    m_is_over = m_isOverHandle(args);
}


void SelectionHandle::mouseDragged(ofMouseEventArgs& args) {
    if (m_is_dragging) {
        m_position.set(args - m_click_offset);
        
        if (m_position.x < m_bounds.x) {
            m_position.x = m_bounds.x;
        } else if (m_position.x > m_bounds.x + m_bounds.width) {
            m_position.x = m_bounds.x + m_bounds.width;
        }
        
        if (m_position.y < m_bounds.y) {
            m_position.y = m_bounds.y;
        } else if (m_position.y > m_bounds.y + m_bounds.height) {
            m_position.y = m_bounds.y + m_bounds.height;
        }
    }
}


void SelectionHandle::mousePressed(ofMouseEventArgs& args) {
    if (m_isOverHandle(args)) {
        m_click_offset.set(args - m_position);
        m_is_dragging = true;
        
        ofNotifyEvent(onHandleDragStart, this);
    }
}


void SelectionHandle::mouseReleased(ofMouseEventArgs& args) {
    if (m_is_dragging) {
        ofNotifyEvent(onHandleDragStop, this);
    }
        
    m_is_dragging = false;
}


const bool SelectionHandle::m_isOverHandle(const ofVec3f& position) {
    const float distance = m_position.distance(position);
    return (distance <= m_radius);
}

