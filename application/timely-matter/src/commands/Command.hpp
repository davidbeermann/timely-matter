#pragma once

#include "AppModel.hpp"
#include "KinectModel.hpp"
#include "ProjectorModel.hpp"
#include "VectorFieldModel.hpp"


namespace timelymatter {
    
    // Base command class for all commands
    class Command {
    protected:
        AppModel& m_app_model;
        KinectModel& m_kinect_model;
        ProjectorModel& m_projector_model;
        VectorFieldModel& m_vector_field_model;
        
    public:
        // Setup model references for all commands derived from this class.
        Command() :
            m_app_model(AppModel::get()),
            m_kinect_model(KinectModel::get()),
            m_projector_model(ProjectorModel::get()),
            m_vector_field_model(VectorFieldModel::get())
        {};
        virtual ~Command() = default;
    };
    
}