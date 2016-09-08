#pragma once

#include "ofMain.h"
#include "AppState.hpp"
#include "AppMode.hpp"


namespace timelymatter {
    
    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class AppEvent {
        // private constructor
        AppEvent() {};
        
    public:
        // static method to retrieve singleton instance
        static AppEvent& get() {
            static AppEvent event;
            return event;
        };
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        AppEvent(AppEvent const&) = delete;
        void operator=(AppEvent const&) = delete;
        
        // events
        ofEvent<void> startup;
        ofEvent<void> reset;
        ofEvent<AppState> update_state;
        ofEvent<void> save_settings;
        ofEvent<void> load_settings;
    };
    
}