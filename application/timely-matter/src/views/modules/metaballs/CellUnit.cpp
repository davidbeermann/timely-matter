#include "CellUnit.hpp"

using namespace timelymatter;


CellUnit::CellUnit(float x, float y) {
    m_position.set(x, y);
    reset();
}


void CellUnit::reset() {
    m_value = 0.f;
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

