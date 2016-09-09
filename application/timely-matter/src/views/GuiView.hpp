#pragma once

#include "BaseView.hpp"
#include "ViewEvent.hpp"
#include "ofMain.h"
#include "ofxGui.h"


namespace timelymatter {

    class GuiView : public BaseView {
        void m_updateInfo();
        
        ViewEvent& m_view_event;
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
        // custom event listeners
        void onGuiUpdate(GuiUpdateArgs& args);
    };
    
}