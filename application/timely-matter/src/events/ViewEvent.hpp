#pragma once

#include "ofMain.h"
#include "AppMode.hpp"


namespace timelymatter {
    
    struct CalibrateProjectionArgs {
        vector<ofVec2f> selection_points;
    };
    
    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class ViewEvent {
        // private constructor
        ViewEvent() {};
        
    public:
        // static method to retrieve singleton instance
        static ViewEvent& get() {
            static ViewEvent event;
            return event;
        };
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        ViewEvent(ViewEvent const&) = delete;
        void operator=(ViewEvent const&) = delete;
        
        // events
        ofEvent<AppMode> mode_selected;
        ofEvent<ofParameterGroup> update_gui;
        ofEvent<CalibrateProjectionArgs> projection_calibrated;
    };
    
}