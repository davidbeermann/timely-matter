#pragma once

#include "Command.hpp"
#include "AppState.hpp"
#include "AppMode.hpp"
#include "AppEvent.hpp"


namespace timelymatter {
    
    class ResetCommand : public Command {
    public:
        void execute() {
            ofLogNotice("ResetCommand") << "execute";
            
            // reset app mode
            m_app_model.setMode(AppMode::UNDEFINED);
            
            // set initial mode
            AppState state = AppState::SELECT_MODE;
            ofNotifyEvent(AppEvent::get().update_state, state, this);
        }
    };
    
}