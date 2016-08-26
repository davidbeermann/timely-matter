#include "RectangularSelection.hpp"

using namespace cv;


void RectangularSelection::setup(const ofRectangle bounds) {
    m_bounds = bounds;
    m_handle_radius = 6.f;
    m_line_color.setHsb(0, 255, 33, 85);
    
    m_handle_tl.setup(bounds, ofVec2f(bounds.x, bounds.y), m_handle_radius);
    m_handle_tr.setup(bounds, ofVec2f(bounds.x + bounds.width, bounds.y), m_handle_radius);
    m_handle_br.setup(bounds, ofVec2f(bounds.x + bounds.width, bounds.y + bounds.height), m_handle_radius);
    m_handle_bl.setup(bounds, ofVec2f(bounds.x, bounds.y + bounds.height), m_handle_radius);
    
    m_handles.push_back(&m_handle_tl);
    m_handles.push_back(&m_handle_tr);
    m_handles.push_back(&m_handle_br);
    m_handles.push_back(&m_handle_bl);
}


void RectangularSelection::draw() {
    ofPushStyle();
    ofSetColor(m_line_color);
    ofDrawLine(m_handle_tl.getPosition(), m_handle_tr.getPosition());
    ofDrawLine(m_handle_tr.getPosition(), m_handle_br.getPosition());
    ofDrawLine(m_handle_br.getPosition(), m_handle_bl.getPosition());
    ofDrawLine(m_handle_bl.getPosition(), m_handle_tl.getPosition());
    ofPopStyle();
    
    m_handle_tl.draw();
    m_handle_tr.draw();
    m_handle_br.draw();
    m_handle_bl.draw();
}


const vector<SelectionHandle*>& RectangularSelection::getHandles() const {
    return m_handles;
}