#include "AppModel.hpp"

using namespace timelymatter;


AppModel::AppModel() {
    // setting default values
    m_state = AppState::INIT;
    m_mode = AppMode::UNDEFINED;
}


AppModel& AppModel::get() {
    static AppModel model;
    return model;
}


const AppState& AppModel::getState() const {
    return m_state;
}


void AppModel::setState(const AppState& state) {
    m_state = state;
    ofNotifyEvent(state_updated, m_state, this);
}


const AppMode& AppModel::getMode() const {
    return m_mode;
}


void AppModel::setMode(const AppMode& mode) {
    m_mode = mode;
    ofNotifyEvent(mode_updated, m_mode, this);
}

