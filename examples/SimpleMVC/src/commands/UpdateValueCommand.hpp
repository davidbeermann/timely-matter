#pragma once

#include "Command.hpp"
#include "AppModel.hpp"


class UpdateValueCommand {
public:
    void execute(int& value) {
        AppModel::get().setValue(value);
    };
};