#pragma once

#include "AppModel.hpp"
#include "BaseView.hpp"
#include "UpdateModeCommand.hpp"


namespace timelymatter {

    class ViewManager {
        void m_clearView();
        void m_setup_view(BaseView* view);
        AppModel& m_app_model;
        BaseView* m_view;
        UpdateModeCommand m_update_mode_cmd;
    public:
        ViewManager();
        ~ViewManager();
        void setup();
        void update();
        void draw();
        void onStateUpdated(AppState& state);
    };

}