#pragma once

#include "Command.hpp"
#include "ViewEvent.hpp"
#include "AppState.hpp"


namespace timelymatter {
    
    class UpdateProjectorCalibrationCommand : public Command {
    public:
        void execute(CalibrateProjectionArgs& args) {
            bool auto_save = true;
            
            if (args.selection_points.size() == 4) {
                ofLog() << "Updated selection points.";
                m_kinect_model.setSelectionPoints(args.selection_points);
            } else {
                auto_save = false;
                ofLog() << "invalid number of selection points: " << args.selection_points.size();
                return;
            }
            
            if (args.depth_clip_near != -1.f) {
                m_kinect_model.setDepthClipNear(args.depth_clip_near);
            } else {
                auto_save = false;
                ofLog() << "Value 'depth_clip_near' undefined: " << args.depth_clip_near;
                return;
            }
            
            if (args.depth_clip_far != -1.f) {
                m_kinect_model.setDepthClipFar(args.depth_clip_far);
            } else {
                auto_save = false;
                ofLog() << "Value 'depth_clip_far' undefined: " << args.depth_clip_near;
                return;
            }
            
            if (auto_save) {
                m_kinect_model.saveSettings();
            } else {
                ofLogError() << "Autosave of Kinect Model failed";
            }
            
            // proceed to next state
            m_app_model.setState(AppState::CALIBRATE_DEPTH);
        }
    };
    
}