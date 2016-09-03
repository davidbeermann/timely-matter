#include "ModeSelectionView.hpp"
#include "BitmapStringUtils.hpp"

using namespace timelymatter;


ModeSelectionView::ModeSelectionView() {
    ofRegisterKeyEvents(this);
}


ModeSelectionView::~ModeSelectionView() {
    ofUnregisterKeyEvents(this);
}


void ModeSelectionView::keyPressed(ofKeyEventArgs& args) {
    // variable needs to be defined, in order to work with event...?
    AppMode mode;
    switch (args.key) {
        case '1':
            mode = AppMode::NOISE;
            ofNotifyEvent(m_view_event.mode_selected, mode, this);
            break;
        case '2':
            mode = AppMode::KINECT;
            ofNotifyEvent(m_view_event.mode_selected, mode, this);
            break;
        default:
            break;
    }
}


void ModeSelectionView::m_onWindowResized(const int width, const int height) {
    ofRectangle box = getBitmapStringBoundingBox(m_message);
    
    // apply padding...
    box.setWidth(box.getWidth() + 2 * m_padding);
    box.setHeight(box.getHeight() + 2 * m_padding);
    
    // ...before calculating position
    box.setX((width - box.getWidth()) * 0.5f);
    box.setY((height - box.getHeight()) * 0.5f);

    // update message position
    m_message_rect.set(box);
}


void ModeSelectionView::m_onSetup() {
    m_message = "Select mode by pressing";
    m_message += "\n(1) for Perlin Noise input";
    m_message += "\n(2) for Kinect 3D input";
    
    m_back_color.setHsb(0, 255*0.75, 255*0.4);
}


void ModeSelectionView::m_onDraw() {
    ofPushMatrix();
    ofTranslate(m_message_rect.getX(), m_message_rect.getY());
    
    ofPushStyle();
    ofSetColor(m_back_color);
    ofDrawRectangle(0, 0, m_message_rect.getWidth(), m_message_rect.getHeight());
    ofPopStyle();
    
    ofTranslate(0, 11);
    ofDrawBitmapString(m_message, m_padding, m_padding);
    
    ofPopMatrix();
}

