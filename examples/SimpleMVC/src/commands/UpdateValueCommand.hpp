#pragma once

#include "Command.hpp"
#include "AppModel.hpp"
#include "IntroView.hpp"


class UpdateValueCommand {
public:
    void execute(IntroViewArgs& args) {
        ofLog() << "updating value to " << args.value << ". Also received value for foo of: " << args.foo;
        AppModel::get().setValue(args.value);
    };
};