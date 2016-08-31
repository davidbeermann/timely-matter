#include "ImageSelection.hpp"
#include "SelectionHandle.hpp"
#include "ofEvents.h"

using namespace cv;


void ImageSelection::setup(const string& image_name) {
    m_image.load(image_name);
    
    m_setup();
}


void ImageSelection::setup(const unsigned int width, const unsigned int height) {
    m_image.allocate(width, height, OF_IMAGE_COLOR);
    m_image.setColor(ofColor(0, 0, 0));
    
    m_setup();
}


void ImageSelection::draw() {
    if (m_mask_enabled && m_redraw_mask) {
        m_drawMask();
    }
    
    ofPushMatrix();
    ofTranslate(m_position);
    if (m_mask_enabled) {
        ofSetColor(255, m_redraw_mask ? 25 : 255);
    }
    else {
        ofSetColor(255);
    }
    m_image.draw(0, 0);
    ofPopMatrix();
    
    m_selection.draw();
}


void ImageSelection::updatePosition(const ofVec2f& position) {
    m_position.set(position.x, position.y);
    m_bounds.set(position.x, position.y, m_image.getWidth(), m_image.getHeight());
    
    m_selection.updateBounds(m_bounds);
}


void ImageSelection::enableMask(const bool value) {
    if (m_mask_enabled) {
        m_clearMask();
    } else {
        m_setupMask();
    }
    
    m_mask_enabled = value;
}


vector<ofVec2f> ImageSelection::getPoints() {
    vector<ofVec2f> points;
    
    vector<SelectionHandle*> handles = m_selection.getHandles();
    for (int i = 0; i < handles.size(); ++i) {
        // convert absolute coordinates to relative coordinates
        points.push_back(ofVec2f(handles[i]->getPosition().x - m_position.x, handles[i]->getPosition().y - m_position.y));
    }
    
    return points;
}


vector<Point2f> ImageSelection::getPointsForCv() {
    vector<Point2f> points;
    
    vector<SelectionHandle*> handles = m_selection.getHandles();
    for (int i = 0; i < handles.size(); ++i) {
        // convert absolute coordinates to relative coordinates
        points.push_back(Point2f(handles[i]->getPosition().x - m_position.x, handles[i]->getPosition().y - m_position.y));
    }
    
    return points;
}


void ImageSelection::m_enableMaskRedraw() {
//    ofLog() << "ImageSelection::_enableMaskRedraw()";
    m_redraw_mask = true;
}


void ImageSelection::m_disableMaskRedraw() {
//    ofLog() << "ImageSelection::m_disableMaskRedraw()";
    m_redraw_mask = false;
}


void ImageSelection::m_setup() {
    m_position.set(0, 0);
    m_bounds.set(0, 0, m_image.getWidth(), m_image.getHeight());
    
    m_selection.setup(m_bounds);
    
    vector<SelectionHandle*> handle;
    for (unsigned int i = 0; i < m_selection.getHandles().size(); ++i) {
        SelectionHandle* handle = m_selection.getHandles().at(i);
        ofAddListener(handle->onHandleDragStart, this, &ImageSelection::m_enableMaskRedraw);
        ofAddListener(handle->onHandleDragStop, this, &ImageSelection::m_disableMaskRedraw);
    }
}


void ImageSelection::m_setupMask() {
    m_mask.allocate(m_image.getWidth(), m_image.getHeight(), GL_RGBA, 8);
    
    m_drawMask();
}


void ImageSelection::m_clearMask() {
    m_mask.clear();
}


void ImageSelection::m_drawMask() {
    ofPath shape;
    shape.setFilled(true);
    shape.setFillColor(ofColor(255));
    vector<SelectionHandle*> handles = m_selection.getHandles();
    shape.moveTo(handles[0]->getPosition() - m_position);
    shape.lineTo(handles[1]->getPosition() - m_position);
    shape.lineTo(handles[2]->getPosition() - m_position);
    shape.lineTo(handles[3]->getPosition() - m_position);
    shape.close();
    
    m_mask.begin();
    ofClear(0);
    shape.draw();
    m_mask.end();
    
    m_image.getTexture().setAlphaMask(m_mask.getTexture());
}

