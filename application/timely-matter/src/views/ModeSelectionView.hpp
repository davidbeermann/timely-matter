#pragma once

#include "ofMain.h"
#include "BaseView.hpp"
#include "AppMode.hpp"


namespace timelymatter
{
    class ModeSelectionView : public BaseView {
        unsigned int m_padding = 30;
        string m_message;
        ofRectangle m_message_rect;
        ofColor m_back_color;
    protected:
        void m_onWindowResized(const int width, const int height);
        void m_onSetup();
        void m_onUpdate() {};
        void m_onDraw();
    public:
        ModeSelectionView();
        ~ModeSelectionView();
        // key event listener methods
        void keyPressed(ofKeyEventArgs& args);
        void keyReleased(ofKeyEventArgs& args) {};
    };
}