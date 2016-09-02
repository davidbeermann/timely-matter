#pragma once

#include "ofMain.h"
#include "AppView.hpp"


class IntroView : public AppView {
    int m_value = -1;
protected:
    void m_doSetup();
    void m_doUpdate();
    void m_doDraw();
public:
    IntroView();
    ~IntroView();
    // view events
    ofEvent<int> update_value;
    // key event handler
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args) {};
    // event handler
    void onValueUpdated(int& value);
};