#pragma once

#include "Command.hpp"
#include "AppState.hpp"


namespace timelymatter {
    
    class UpdateStateCommand : public Command {
    public:
        void execute(AppState& state) {
            if (m_app_model.getState() != state) {
                ofLog() << "State updated: " << (int) state;
                m_app_model.setState(state);
            } else {
                ofLog() << "State update neglected: " << (int) state;
            }
        }
    };
    
}