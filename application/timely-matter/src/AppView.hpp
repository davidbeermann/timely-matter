#pragma once

#include "ofMain.h"
#include "ofEvents.h"


class AppView {
protected:
    virtual void m_onWindowResized(const int width, const int height) = 0;
public:
    AppView() {
//        ofLog() << "AppView()";
        ofAddListener(ofEvents().windowResized, this, &AppView::onWindowResized);
    };
    ~AppView() {
//        ofLog() << "~AppView()";
        ofRemoveListener(ofEvents().windowResized, this, &AppView::onWindowResized);
    };
    void onWindowResized(ofResizeEventArgs& args) {
//        ofLog() << "AppView::onWindowResized";
        m_onWindowResized(args.width, args.height);
    };
};