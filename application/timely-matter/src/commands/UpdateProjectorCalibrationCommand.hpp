#pragma once

#include "Command.hpp"
#include "ViewEvent.hpp"
#include "AppState.hpp"


namespace timelymatter {
    
    class UpdateProjectorCalibrationCommand : public Command {
    public:
        void execute(CalibrateProjectionArgs& args) {
            if (args.selection_points.size() == 4) {
                ofLog() << "Updated selection points.";
                m_kinect_model.setSelectionPoints(args.selection_points);
                
                m_app_model.setState(AppState::CALIBRATE_DEPTH);
            } else {
                ofLog() << "invalid number of selection points: " << args.selection_points.size();
            }
        }
    };
    
}