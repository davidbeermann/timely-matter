#pragma once

#include "ofMain.h"
#include "VectorFieldInputProvider.h"


// C++11 enum classes are strongly typed!
// http://www.cplusplus.com/forum/general/147341/
// http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html
// Why my old C-style enum implementation didn't work...
// http://stackoverflow.com/questions/12183008/how-to-use-enums-in-c
enum class VectorFieldInputType : uint8_t {
    NOISE = 1,
    KINECT = 2
};


class VectorFieldInputFactory {
public:
    VectorFieldInputProvider* get(VectorFieldInputType type);
};