#pragma once


// C++11 enum classes are strongly typed!
// http://www.cplusplus.com/forum/general/147341/
// http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html
// Why my old C-style enum implementation didn't work...
// http://stackoverflow.com/questions/12183008/how-to-use-enums-in-c
enum class Directions : char {
    NORTH_WEST = 1,
    NORTH = 2,
    NORTH_EAST = 3,
    EAST = 4,
    SOUTH_EAST = 5,
    SOUTH = 6,
    SOUTH_WEST = 7,
    WEST = 8
};
