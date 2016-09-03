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
            m_setup_view(new ModeSelectionView());
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


void ViewManager::m_setup_view(BaseView* view) {
    // clear old view
    m_clearView();
    
    // setup new view
    m_view = view;
    m_view->setup();
}
