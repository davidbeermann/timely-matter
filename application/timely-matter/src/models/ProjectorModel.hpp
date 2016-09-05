#pragma once

#include "ofMain.h"


namespace timelymatter {
    
    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class ProjectorModel {
        // private constructor
        ProjectorModel();
        
        ofRectangle m_size;
        
    public:
        // static method to retrieve singleton instance
        static ProjectorModel& get();
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        ProjectorModel(ProjectorModel const&) = delete;
        void operator=(ProjectorModel const&) = delete;
        
        // public interface methods
        const unsigned int getWidth() const;
        const unsigned int getHeight() const;
        const ofRectangle getSize() const;
        void setSize(const unsigned int& width, const unsigned int& height);
    };
    
}