#pragma once

#include "Command.hpp"
#include "AppMode.hpp"
#include "AppState.hpp"


namespace timelymatter {
    
    class UpdateModeCommand : public Command {
    public:
        void execute(AppMode& mode) {
            if (m_app_model.getMode() != mode) {
                ofLog() << "Mode update to: " << (int) mode;
                m_app_model.setMode(mode);
                
                switch (mode) {
                    case AppMode::NOISE:
                        m_app_model.setState(AppState::RENDER);
                        break;
                    case AppMode::KINECT:
                        m_app_model.setState(AppState::CALIBRATE_PROJECTION);
                        break;
                    default:
                        ofLog() << "The logic for the mode " << (int) mode << " is not implemented.";
                        break;
                }
            }
        }
    };
    
}
