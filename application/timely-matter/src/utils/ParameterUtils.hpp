#pragma once

#include "ofMain.h"
#include "KinectModel.hpp"
#include "VectorFieldModel.hpp"


namespace timelymatter
{
    inline ofParameterGroup& setupDepthClippingParameters
    (
        ofParameterGroup& group,
        ofParameter<unsigned int>& near,
        ofParameter<unsigned int>& far
    ) {
        KinectModel& kinect_model = KinectModel::get();
        
        // set names for loading settings
        group.setName("Depth Clipping");
        near.setName("near");
        far.setName("far");
        
        // apply values stored in model
        near.set(kinect_model.getDepthClipNear());
        near.setMin(kinect_model.getDepthClipNearMin());
        near.setMax(kinect_model.getDepthClipNearMax());
        
        far.set(kinect_model.getDepthClipFar());
        far.setMin(kinect_model.getDepthClipFarMin());
        far.setMax(kinect_model.getDepthClipFarMax());
        
        // add parameters to group
        group.add(near);
        group.add(far);
        
        // return group
        return group;
    }
    
    
    inline ofParameterGroup& setupInfraredParameters
    (
        ofParameterGroup& group,
        ofParameter<float>& min,
        ofParameter<float>& max
    ) {
        // setup parameters for loading settings
        group.setName("Infrared Normalization");
        group.add(min.set("min", 33.f, 0.f, 255.f));
        group.add(max.set("max", 255.f, 0.f, 255.f));
        
        // return group
        return group;
    }
    
    
    inline ofParameterGroup& setupVectorFieldParameters
    (
        ofParameterGroup& group,
        ofParameter<float>& edge_force,
        ofParameter<float>& field_force,
        ofParameter<float>& attract_threshold,
        ofParameter<bool>& show_marks,
        ofParameter<bool>& show_values,
        ofParameter<bool>& show_vectors
    ) {
        // get model reference
        VectorFieldModel& model = VectorFieldModel::get();
        
        // set name
        group.setName("Vector Field");
        edge_force.setName("edge force");
        field_force.setName("field force");
        attract_threshold.setName("attract threshold");
        show_marks.setName("show marks");
        show_values.setName("show values");
        show_vectors.setName("show vectors");
        
        // set values
        edge_force.set(model.getEdgeForce());
        edge_force.setMin(model.getEdgeForceMin());
        edge_force.setMax(model.getEdgeForceMax());
        
        field_force.set(model.getFieldForce());
        field_force.setMin(model.getFieldForceMin());
        field_force.setMax(model.getFieldForceMax());
        
        attract_threshold.set(model.getAttractThreshold());
        attract_threshold.setMin(0.f);
        attract_threshold.setMax(255.f);
        
        show_marks.set(false);
        show_values.set(false);
        show_vectors.set(false);
        
        // add parameters to group
        group.add(edge_force);
        group.add(field_force);
        group.add(attract_threshold);
        group.add(show_marks);
        group.add(show_values);
        group.add(show_vectors);
        
        // return
        return group;
    }
}