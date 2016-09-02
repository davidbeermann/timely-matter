#pragma once

#include "ofMain.h"
#include "AppModel.hpp"


class AppView {
protected:
    AppModel& m_model;
    // methods to be implemented by concrete view
    virtual void m_doSetup() = 0;
    virtual void m_doUpdate() = 0;
    virtual void m_doDraw() = 0;
public:
    // setup model reference for all views
    AppView() : m_model(AppModel::get()) { ofLog() << "AppView()"; };
    // always define virtual destructors for base classes
    // http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors#461224
    virtual ~AppView() { ofLog() << "~AppView()"; };
    // non virtual public interface
    void setup() { m_doSetup(); };
    void update() { m_doUpdate(); };
    void draw() { m_doDraw(); };
};