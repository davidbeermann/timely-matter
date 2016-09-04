#include "VectorFieldModel.hpp"

using namespace timelymatter;


VectorFieldModel::VectorFieldModel() {
    // set default values
    m_field_force = 8.f;
    m_field_force_min = 0.f;
    m_field_force_max = 12.f;
    m_edge_force = 8.f;
    m_edge_force_min = 0.f;
    m_edge_force_max = 12.f;
}


VectorFieldModel& VectorFieldModel::get() {
    static VectorFieldModel model;
    return model;
}


void VectorFieldModel::setFieldForce(const unsigned int& value) {
    if (value >= m_field_force_min && value <= m_field_force_max) {
        m_field_force = value;
    } else {
        ofLog() << "Out of range value for field force. Must be within [" << m_field_force_min << "," << m_field_force_max << "]";
    }
}


void VectorFieldModel::setEdgeForce(const unsigned int& value) {
    if (value >= m_edge_force_min && value <= m_edge_force_max) {
        m_edge_force = value;
    } else {
        ofLog() << "Out of range value for edge force. Must be within [" << m_edge_force_min << "," << m_edge_force_max << "]";
    }
}
