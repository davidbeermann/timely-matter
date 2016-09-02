#pragma once

#include "Command.hpp"


class ChangeStateCommand : public Command {
public:
    void execute(AppState& state) {
        if (m_model.getState() != state) {
            ofLog() << "State is now: " << (int) state;
            m_model.setState(state);
        } else {
            ofLog() << "State change to " << (int) state << " is neglected";
        }
    };
};