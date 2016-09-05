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
        float m_attract_threshold;
        
    public:
        // static method to retrieve singleton instance
        static VectorFieldModel& get();
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        VectorFieldModel(VectorFieldModel const&) = delete;
        void operator=(VectorFieldModel const&) = delete;
        
        // public interface methods
        void setFieldForce(const float& value);
        const float getFieldForce() const {
            return m_field_force;
        }
        const float getFieldForceMin() const {
            return m_field_force_min;
        }
        const float getFieldForceMax() const {
            return m_field_force_max;
        }
        
        void setEdgeForce(const float& value);
        const float getEdgeForce() const {
            return m_edge_force;
        }
        const float getEdgeForceMin() const {
            return m_edge_force_min;
        }
        const float getEdgeForceMax() const {
            return m_edge_force_max;
        }
        
        const float getAttractThreshold() const {
            return m_attract_threshold;
        }
    };
    
}