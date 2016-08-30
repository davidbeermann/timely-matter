#pragma once

#include "ofEvents.h"


// Class adapted from proposed singleton class found here:
// http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
class ViewEvents {
private:
    ViewEvents() {};
    // C++ 03
//    ViewEvents(ViewEvents const&);     // Don't Implement
//    void operator=(ViewEvents const&); // Don't implement
public:
    static ViewEvents& get() {
        static ViewEvents instance;
        return instance;
    }
    // C++ 11
    ViewEvents(ViewEvents const&) = delete;
    void operator=(ViewEvents const&) = delete;
    
    ofEvent<void> onParametersChanged;
    ofEvent<void> onKinectCalibrated;
};

