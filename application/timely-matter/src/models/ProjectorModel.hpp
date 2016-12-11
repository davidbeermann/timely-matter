#pragma once

#include "ofMain.h"


namespace timelymatter {
    
    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class ProjectorModel {
        // private constructor
        ProjectorModel();
        
        ofRectangle m_output;
        ofRectangle m_buffer;
        
    public:
        // static method to retrieve singleton instance
        static ProjectorModel& get();
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        ProjectorModel(ProjectorModel const&) = delete;
        void operator=(ProjectorModel const&) = delete;
        
        // public interface methods
        const unsigned int getOutputWidth() const;
        const unsigned int getOutputHeight() const;
        const ofRectangle & getOutputSize() const;
        const unsigned int getBufferWidth() const;
        const unsigned int getBufferHeight() const;
        const ofRectangle & getBufferSize() const;
        void setSize(const unsigned int& output_width, const unsigned int& output_height, const unsigned int& buffer_width, const unsigned int& buffer_height);
    };
    
}