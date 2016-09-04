#pragma once

#include "Command.hpp"
#include "ViewEvent.hpp"
#include "AppState.hpp"


namespace timelymatter {
    
    class UpdateDepthCalibrationCommand : public Command {
    public:
        void execute(CalibrateDepthArgs& args) {
            
//            ofLog() << "depth_clip_near: " << args.depth_clip_near;
//            ofLog() << "depth_clip_far: " << args.depth_clip_far;
//            ofLog() << "vector_force_field: " << args.vector_force_field;
//            ofLog() << "vector_force_edge: " << args.vector_force_edge;
            
            if (args.depth_clip_near != -1.f) {
                m_kinect_model.setDepthClipNear(args.depth_clip_near);
            } else {
                ofLog() << "Value 'depth_clip_near' undefined: " << args.depth_clip_near;
                return;
            }
            
            if (args.depth_clip_far != -1.f) {
                m_kinect_model.setDepthClipFar(args.depth_clip_far);
            } else {
                ofLog() << "Value 'depth_clip_far' undefined: " << args.depth_clip_near;
                return;
            }
            
            if (args.vector_force_field != -1.f) {
                m_vector_field_model.setFieldForce(args.vector_force_field);
            } else {
                ofLog() << "Value 'vector_force_field' undefined: " << args.vector_force_field;
                return;
            }
            
            if (args.vector_force_edge != -1.f) {
                m_vector_field_model.setEdgeForce(args.vector_force_edge);
            } else {
                ofLog() << "Value 'vector_force_edge' undefined: " << args.vector_force_edge;
                return;
            }
            
            // set next state
            m_app_model.setState(AppState::RENDER);
        }
    };

}