#pragma once

#include "AppModel.hpp"


class Command {
protected:
    AppModel& m_model;
public:
    Command() : m_model(AppModel::get()) {};
};