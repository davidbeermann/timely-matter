#pragma once

#include "AppModel.hpp"
#include "AppView.hpp"
#include "UpdateValueCommand.hpp"


class ViewManager {
    void m_clearView();
    void m_setup_intro_view();
    void m_setup_outro_view();
    AppModel& m_model;
    AppView* m_view;
    UpdateValueCommand m_update_value_cmd;
public:
    ViewManager();
    ~ViewManager();
    void setup();
    void update();
    void draw();
    void onStateUpdated(AppState& state);
};