#pragma once

#include "ofMain.h"


namespace timelymatter {
    
    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class VectorFieldModel {
        // private constructor
        VectorFieldModel();
        
        float m_field_force;
        float m_field_force_min;
        float m_field_force_max;
        float m_edge_force;
        float m_edge_force_min;
        float m_edge_force_max;
        
    public:
        // static method to retrieve singleton instance
        static VectorFieldModel& get();
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        VectorFieldModel(VectorFieldModel const&) = delete;
        void operator=(VectorFieldModel const&) = delete;
        
        // public interface methods
        void setFieldForce(const unsigned int& value);
        const unsigned int getFieldForce() const {
            return m_field_force;
        }
        const unsigned int getFieldForceMin() const {
            return m_field_force_min;
        }
        const unsigned int getFieldForceMax() const {
            return m_field_force_max;
        }
        
        void setEdgeForce(const unsigned int& value);
        const unsigned int getEdgeForce() const {
            return m_edge_force;
        }
        const unsigned int getEdgeForceMin() const {
            return m_edge_force_min;
        }
        const unsigned int getEdgeForceMax() const {
            return m_edge_force_max;
        }
    };
    
}