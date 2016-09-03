#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "AppModel.hpp"
#include "KinectModel.hpp"
#include "ViewEvent.hpp"


namespace timelymatter
{
    
// Base view class to be extended by concrete views managed by ViewManager class.
// Implementation for NVI Non-Virtual Interface derived from here:
// http://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11#answer-14324500
class BaseView {
protected:
    AppModel& m_app_model;
    KinectModel& m_kinect_model;
    ViewEvent& m_view_event;
    
    // Methods to be implemented by concrete view.
    virtual void m_onWindowResized(const int width, const int height) = 0;
    virtual void m_onSetup() = 0;
    virtual void m_onUpdate() = 0;
    virtual void m_onDraw() = 0;
    
public:
    // Setup model references for all views derived from this class.
    BaseView() :
    m_app_model(AppModel::get()),
    m_kinect_model(KinectModel::get()),
    m_view_event(ViewEvent::get()) {
        ofAddListener(ofEvents().windowResized, this, &BaseView::onWindowResized);
    };
    
    // always define virtual destructors for base classes
    // http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors#461224
    virtual ~BaseView() {
        ofRemoveListener(ofEvents().windowResized, this, &BaseView::onWindowResized);
    };
    
    // event listener methods
    void onWindowResized(ofResizeEventArgs& args) {
        m_onWindowResized(args.width, args.height);
    };
    
    // Non-Virtual Interface methods
    void setup() {
        // call setup first...
        m_onSetup();
        // ...before triggering a virtual window resize.
        m_onWindowResized(ofGetWindowWidth(), ofGetWindowHeight());
    };
    void update() { m_onUpdate(); };
    void draw() { m_onDraw(); };
};
    
}