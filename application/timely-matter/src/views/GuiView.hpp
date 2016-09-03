#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "BaseView.hpp"


namespace timelymatter {

    class GuiView : public BaseView {
        bool m_visible;
        ofxPanel m_panel;
        string m_info;
        ofRectangle m_info_rect;
        int m_info_padding;
        ofColor m_info_bg_color;
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate();
        void m_onDraw();
    public:
        GuiView();
        ~GuiView();
        // key event listener methods
        void keyPressed(ofKeyEventArgs& args);
        void keyReleased(ofKeyEventArgs& args) {};
    };
    
}