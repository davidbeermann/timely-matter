#pragma once

#include "ofMain.h"
#include "AppState.hpp"
#include "AppMode.hpp"


namespace timelymatter {

    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class AppModel {
        // private constructor
        AppModel();
        
        AppState m_state;
        AppMode m_mode;
        
    public:
        // static method to retrieve singleton instance
        static AppModel& get();
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        AppModel(AppModel const&) = delete;
        void operator=(AppModel const&) = delete;
        
        // public interface methods
        const AppState& getState() const;
        void setState(const AppState& state);
        const AppMode& getMode() const;
        void setMode(const AppMode& mode);
        
        // events
        ofEvent<AppState> state_updated;
        ofEvent<AppMode> mode_updated;
    };

}