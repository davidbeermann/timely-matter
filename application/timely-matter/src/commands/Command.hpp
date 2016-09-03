#pragma once

#include "AppModel.hpp"
#include "KinectModel.hpp"


namespace timelymatter {
    
    // Base command class for all commands
    class Command {
    protected:
        AppModel& m_app_model;
        KinectModel& m_kinect_model;
    public:
        // Setup model references for all commands derived from this class.
        Command() : m_app_model(AppModel::get()), m_kinect_model(KinectModel::get()) {};
        virtual ~Command() = default;
    };
    
}