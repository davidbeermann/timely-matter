#pragma once

#include "Command.hpp"


namespace timelymatter {
    
    class SaveSettingsCommand : public Command {
    public:
        void execute() {
            ofLogNotice("SaveSettingsCommand") << "execute";
            
            // save model settings
            m_kinect_model.saveSettings();
        }
    };
    
}