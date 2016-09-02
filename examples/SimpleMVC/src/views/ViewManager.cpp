#include "ViewManager.hpp"
#include "IntroView.hpp"
#include "OutroView.hpp"


ViewManager::ViewManager() : m_model(AppModel::get()) {
    m_view = nullptr;
}


ViewManager::~ViewManager() {
    m_clearView();
}


void ViewManager::setup() {
    ofAddListener(m_model.state_updated, this, &ViewManager::onStateUpdated);
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
        case AppState::INTRO:
            m_setup_intro_view();
            break;
        case AppState::OUTRO:
            m_setup_outro_view();
            break;
        default:
            break;
    }
}


void ViewManager::m_clearView() {
    if (m_view != nullptr) {
        delete m_view;
        m_view = nullptr;
    }
}


void ViewManager::m_setup_intro_view() {
    m_clearView();
    
    m_view = new IntroView();
    m_view->setup();
    
    IntroView* view = static_cast<IntroView*>(m_view);
    ofAddListener(view->update_value, &m_update_value_cmd, &UpdateValueCommand::execute);
}


void ViewManager::m_setup_outro_view() {
    m_clearView();
    
    m_view = new OutroView();
    m_view->setup();
}
