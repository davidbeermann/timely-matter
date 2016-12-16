#include "GuiView.hpp"
#include "BitmapStringUtils.hpp"
#include "AppEvent.hpp"

using namespace timelymatter;


void GuiView::m_updateInfo() {
    m_info = "FPS: " + to_string((int) ofGetFrameRate());
    m_info += "\nCurrent App Mode: " + to_string((int) m_app_model.getMode());
    m_info += "\nCurrent App State: " + to_string((int) m_app_model.getState());
    
    ofRectangle bounds = getBitmapStringBoundingBox(m_info);
    // update dimensions
    m_info_rect.setWidth(bounds.getWidth() + 2 * m_info_padding);
    m_info_rect.setHeight(bounds.getHeight() + 2 * m_info_padding);
}


void GuiView::m_onWindowResized(const int width, const int height) {
}


void GuiView::m_onSetup() {
    // hide initially
    m_visible = false;
    
    // configure gui panel
    m_panel.setDefaultWidth(250);
    m_panel.setWidthElements(250);
    m_panel.setup("Timely Matter");
    
    m_info_padding = 15;
    m_info_bg_color.set(0, 0, 0, 255*0.9);
    
    m_info_rect.setX(8.f);
    m_info_rect.setY(8.f);
    
    // set initial gui position
    m_updateInfo();
    m_panel.setPosition(m_info_rect.getX() + m_info_rect.getWidth() + 8.f, m_info_rect.getY());
    
    // add listener for updates
    ofAddListener(m_view_event.update_gui, this, &GuiView::onGuiUpdate);
}


void GuiView::m_onUpdate() {
    if (m_visible) {
        m_updateInfo();
    }
}


void GuiView::m_onDraw() {
    if (m_visible) {
        ofPushStyle();
        ofSetColor(m_info_bg_color);
        ofDrawRectangle(m_info_rect);
        ofPopStyle();
        
        ofPushMatrix();
        ofTranslate(m_info_rect.getX() + m_info_padding, m_info_rect.getY() + m_info_padding);
        ofDrawBitmapString(m_info, 0, 11);
        ofPopMatrix();
        
        m_panel.draw();
    }
}


GuiView::GuiView() : m_view_event(ViewEvent::get()) {
    ofRegisterKeyEvents(this);
}


GuiView::~GuiView() {
    ofUnregisterKeyEvents(this);
}


void GuiView::keyPressed(ofKeyEventArgs& args) {
    // solution for scope issues in case statements.
    // foud here: http://stackoverflow.com/questions/92396/why-cant-variables-be-declared-in-a-switch-statement
    switch (args.key) {
        case 'g': {
            m_visible = !m_visible;
            break;
        }
        case 'r': {
            ofNotifyEvent(AppEvent::get().reset, this);
            m_panel.clear();
            break;
        }
        case 's': {
            ofNotifyEvent(AppEvent::get().save_settings, this);
            break;
        }
        case 'l': {
            ofNotifyEvent(AppEvent::get().load_settings, this);
            break;
        }
    }
}

void GuiView::onGuiUpdate(GuiUpdateArgs& args) {
    // clear out all previous paramters
    m_panel.clear();
    
    // add parameters send via event
    if (args.params.size() > 0) {
        for (int i = 0; i < args.params.size(); ++i) {
            // check if parameter group contains parameters ...
            if (args.params[i].size() > 0) {
                // ... add the group to the panel.
                m_panel.add(args.params[i]);
            }
        }
    }
    
    // load settings
    m_panel.loadFromFile("settings.xml");
}

