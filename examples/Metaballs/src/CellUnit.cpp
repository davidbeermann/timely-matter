#include "CellUnit.hpp"


CellUnit::CellUnit(float x, float y) {
    m_position.set(x, y);
    reset();
}


void CellUnit::reset() {
    m_value = 0.f;
    m_color.set(0, 0, 0, 0);
}


const ofVec3f& CellUnit::getPosition() {
    return m_position;
}


void CellUnit::addValue(const float value) {
    m_value += value;
}


const float CellUnit::getValue() {
    return m_value;
}


const ofColor & CellUnit::getColor() {
    return m_color;
}


void CellUnit::setColor(const ofColor & color) {
    m_color = color;
}

