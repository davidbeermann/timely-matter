#pragma once

#include "ofMain.h"


// C++11 enum classes are strongly typed!
// http://www.cplusplus.com/forum/general/147341/
// http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html
// Why my old C-style enum implementation didn't work...
// http://stackoverflow.com/questions/12183008/how-to-use-enums-in-c


enum class AppMode : uint8_t {
    NOISE = 1,
    KINECT = 2
};


enum class AppState : uint8_t {
    MODE_SELECTION = 1,
    CALIBRATION = 2,
    RUNNING = 3
};

