#pragma once

#include "ofMain.h"
#include "KinectModel.hpp"


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
        near.setName("Near");
        far.setName("Far");
        
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
}