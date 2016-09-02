#pragma once

#include "ofMain.h"
#include "AppView.hpp"


class OutroView : public AppView {
    int m_value = -1;
protected:
    void m_doSetup();
    void m_doUpdate();
    void m_doDraw();
public:
    OutroView();
    ~OutroView();
};