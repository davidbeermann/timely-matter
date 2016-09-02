#include "AppModel.hpp"
#include "AppEvents.hpp" // include here instead of header due to cyclical dependency


AppModel::AppModel() : m_events(AppEvents::get()) {
    m_state = AppState::INIT;
}


AppModel& AppModel::get() {
    static AppModel model;
    return model;
}


const AppState& AppModel::getState() const {
    return m_state;
}


void AppModel::setState(AppState& state) {
    m_state = state;
    ofNotifyEvent(state_updated, m_state, this);
}


const int& AppModel::getValue() const {
    return m_value;
}


void AppModel::setValue(const int value) {
    m_value = value;
    ofNotifyEvent(value_updated, m_value, this);
}

