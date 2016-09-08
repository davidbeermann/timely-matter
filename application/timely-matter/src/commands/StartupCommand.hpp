#pragma once

#include "Command.hpp"
#include "AppState.hpp"
#include "AppEvent.hpp"


namespace timelymatter {
    
    class StartupCommand : public Command {
    public:
        void execute() {
            ofLogNotice("StartupCommand") << "execute";
            
            // load model settings
            m_kinect_model.loadSettings();
            
            // set initial state
            AppState state = AppState::SELECT_MODE;
            ofNotifyEvent(AppEvent::get().update_state, state, this);
        }
    };
    
}