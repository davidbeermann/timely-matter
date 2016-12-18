#pragma once

#include "ofMain.h"
#include "RenderParams.hpp"


namespace timelymatter {
    
    // Base view class to be extended by concrete views managed by ViewManager class.
    // Implementation for NVI Non-Virtual Interface derived from here:
    // http://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11#answer-14324500
    class RenderControls {
        
    protected:
        // provide easy access to parameters
        RenderParams & m_params = RenderParams::get();
        
        // Methods to be implemented by concrete view.
        virtual void m_onSetup() = 0;
        virtual void m_onUpdate() = 0;
        
    public:
        // always define virtual destructors for base classes
        // http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors#461224
        // C++11 style
        virtual ~RenderControls() = default;
        
        // Non-Virtual Interface methods
        void setup() { m_onSetup(); };
        void update() { m_onUpdate(); };
    };
    
}