#pragma once

#include "ofMain.h"
#include "BaseView.hpp"
#include "AppMode.hpp"


namespace timelymatter {

    // Base view class to be extended by concrete views managed by ViewManager class.
    // Implementation for NVI Non-Virtual Interface derived from here:
    // http://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11#answer-14324500
    class VectorFieldInput : public BaseView {
        
    protected:
        // Methods to be implemented by concrete view.
        virtual void m_onDraw(const ofRectangle& size) = 0;
        virtual ofParameterGroup& m_onGetParams() = 0;
        virtual const ofPixels& m_onGetPixels() = 0;
        virtual const unsigned int m_onGetWidth() = 0;
        virtual const unsigned int m_onGetHeight() = 0;
        virtual const AppMode m_onGetType() = 0;
        virtual const string m_onGetName() = 0;
        
    public:
        // always define virtual destructors for base classes
        // http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors#461224
        // C++11 style
        virtual ~VectorFieldInput() = default;
        
        // Non-Virtual Interface methods
        void draw(const ofRectangle& size) { m_onDraw(size); };
        ofParameterGroup& getParams() { return m_onGetParams(); };
        const ofPixels& getPixels() { return m_onGetPixels(); };
        const unsigned int getWidth() { return m_onGetWidth(); };
        const unsigned int getHeight() { return m_onGetHeight(); };
        const AppMode getType() { return m_onGetType(); };
        const string getName() { return m_onGetName(); };
    };

}

