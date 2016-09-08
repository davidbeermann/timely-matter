#pragma once

#include "Command.hpp"


namespace timelymatter {
    
    class LoadSettingsCommand : public Command {
    public:
        void execute() {
            ofLogNotice("LoadSettingsCommand") << "execute";
            
            // save model settings
            m_kinect_model.loadSettings();
        }
    };
    
}