#pragma once

#include "Command.hpp"
#include "AppMode.hpp"


namespace timelymatter {
    
    class UpdateModeCommand : public Command {
    public:
        void execute(AppMode& mode) {
            if (m_app_model.getMode() != mode) {
                ofLog() << "Mode update to: " << (int) mode;
                m_app_model.setMode(mode);
            }
        }
    };
    
}
