#pragma once

#include "ofMain.h"


namespace timelymatter
{
    enum class AppState : uint8_t {
        INIT = 0,
        SELECT_MODE = 1,
        CALIBRATE_PROJECTION = 2,
        CALIBRATE_DEPTH = 3,
        RENDER = 4
    };
}

