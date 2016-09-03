#include "RectangularSelection.hpp"
#include "ofEvents.h"

using namespace timelymatter;
using namespace cv;


void RectangularSelection::setup(const ofRectangle& bounds) {
    m_bounds = bounds;
    m_handle_radius = 6.f;
    m_line_color.setHsb(0, 255, 255, 85);
    
    m_handle_tl.setup(bounds, ofVec2f(bounds.x, bounds.y), m_handle_radius);
    m_handle_tr.setup(bounds, ofVec2f(bounds.x + bounds.width, bounds.y), m_handle_radius);
    m_handle_br.setup(bounds, ofVec2f(bounds.x + bounds.width, bounds.y + bounds.height), m_handle_radius);
    m_handle_bl.setup(bounds, ofVec2f(bounds.x, bounds.y + bounds.height), m_handle_radius);
    
    // Creating a vector of type vector<SelectionHandle> leads to weird errors – destruction of instances inside of vector.
    // Therefore a vector of pointers is used.
    m_handles.push_back(&m_handle_tl); // 0 = top left
    m_handles.push_back(&m_handle_tr); // 1 = top right
    m_handles.push_back(&m_handle_br); // 2 = bottom tight
    m_handles.push_back(&m_handle_bl); // 3 = bottom left
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


void RectangularSelection::updateBounds(const ofRectangle& bounds) {
    m_bounds = bounds;
    
    for (int i = 0; i < m_handles.size(); ++i) {
        SelectionHandle* handle = m_handles.at(i);
        handle->updateBounds(bounds);
    }
}


vector<SelectionHandle*>& RectangularSelection::getHandles() {
    return m_handles;
}