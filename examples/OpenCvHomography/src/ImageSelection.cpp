#include "ImageSelection.hpp"
#include "SelectionHandle.hpp"

using namespace cv;


void ImageSelection::_setup() {
    m_bounds.set(m_position.x, m_position.y, m_image.getWidth(), m_image.getHeight());
    m_selection.setup(m_bounds);
}


void ImageSelection::_setupMask() {
    m_mask.allocate(m_image.getWidth(), m_image.getHeight(), GL_RGBA, 8);
    
    _drawMask();
}


void ImageSelection::_clearMask() {
    m_mask.clear();
}


void ImageSelection::_drawMask() {
    ofPath shape;
    shape.setFilled(true);
    shape.setFillColor(ofColor(255));
    const vector<SelectionHandle*> handles = m_selection.getHandles();
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


void ImageSelection::setup(const ofVec2f& position, const string& image_name) {
    m_position = position;
    
    m_image.load(image_name);
    
    _setup();
}


void ImageSelection::setup(const ofVec2f& position, const unsigned int width, const unsigned int height) {
    m_position = position;
    
    m_image.allocate(width, height, OF_IMAGE_COLOR);
    m_image.setColor(ofColor(0, 0, 0));
    
    _setup();
}


void ImageSelection::draw() {
    if (m_mask_enabled) {
        _drawMask();
    }
    
    ofPushMatrix();
    ofTranslate(m_position);
    m_image.draw(0, 0);
    ofPopMatrix();
    
    m_selection.draw();
}


const vector<Point2f> ImageSelection::getPoints() {
    vector<Point2f> points;
    
    const vector<SelectionHandle*> handles = m_selection.getHandles();
    for (int i = 0; i < handles.size(); ++i) {
        points.push_back(Point2f(handles[i]->getPosition().x - m_position.x, handles[i]->getPosition().y - m_position.y));
    }
    
    return points;
}


void ImageSelection::enableMask(const bool value) {
    if (m_mask_enabled) {
        _clearMask();
    } else {
        _setupMask();
    }
    
    m_mask_enabled = value;
}

