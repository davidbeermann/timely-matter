#pragma once

#include "ofMain.h"
#include "AppModel.hpp"


class AppEvents {
    // private constructor
    AppEvents() {};
public:
    static AppEvents& get() {
        static AppEvents events;
        return events;
    }
    
    // remove copy constructor and and copy assingment operator - C++ 11 style
    AppEvents(AppEvents const&) = delete;
    void operator=(AppEvents const&) = delete;
    
    // events to subscribe to
    ofEvent<AppState> change_state;
};