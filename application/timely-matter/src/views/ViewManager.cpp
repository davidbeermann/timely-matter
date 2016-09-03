#include "ViewManager.hpp"
#include "ModeSelectionView.hpp"


using namespace timelymatter;


ViewManager::ViewManager() : m_app_model(AppModel::get()) {
    m_view = nullptr;
}


ViewManager::~ViewManager() {
    m_clearView();
}


void ViewManager::setup() {
    ofAddListener(m_app_model.state_updated, this, &ViewManager::onStateUpdated);
}


void ViewManager::update() {
    if (m_view != nullptr) {
        m_view->update();
    }
}


void ViewManager::draw() {
    if (m_view != nullptr) {
        m_view->draw();
    }
}


void ViewManager::onStateUpdated(AppState& state) {
    switch (state) {
        case AppState::SELECT_MODE:
            m_setup_mode_selection_view();
            break;
        default:
            ofLog() << "No case implemented for state " << (int) state;
            break;
    }
}


void ViewManager::m_clearView() {
    if (m_view != nullptr) {
        delete m_view;
        m_view = nullptr;
    }
}


void ViewManager::m_setup_mode_selection_view() {
    m_clearView();
    
    m_view = new ModeSelectionView();
    m_view->setup();
    
    ModeSelectionView* view = static_cast<ModeSelectionView*>(m_view);
    ofAddListener(view->mode_selected, &m_update_mode_cmd, &UpdateModeCommand::execute);
}
