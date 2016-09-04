#pragma once


namespace timelymatter
{

    // C++11 enum classes are strongly typed!
    // http://www.cplusplus.com/forum/general/147341/
    // http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html
    // Why my old C-style enum implementation didn't work...
    // http://stackoverflow.com/questions/12183008/how-to-use-enums-in-c

    // Any combination of directions will result in a unique number!
    enum class Directions : uint8_t {
        NORTH_WEST = 1,
        NORTH = 2,
        NORTH_EAST = 4,
        EAST = 8,
        SOUTH_EAST = 16,
        SOUTH = 32,
        SOUTH_WEST = 64,
        WEST = 128
    };

    // These are the results of the possible combinations within the grid.
    class DirectionIndex {
    public:
        // EAST + SOUTH_EAST + SOUTH
        // 8 + 16 + 32
        static const uint8_t TOP_LEFT = 56;
        // SOUTH + SOUTH_WEST + WEST
        // 32 + 64 + 128
        static const uint8_t TOP_RIGHT = 224;
        // WEST + NORTH_WEST + NORTH
        // 128 + 1 + 2
        static const uint8_t BOTTOM_RIGHT = 131;
        // NORTH + NORTH_EAST + EAST
        // 2 + 4 + 8
        static const uint8_t BOTTOM_LEFT = 14;
        // EAST + SOUTH_EAST + SOUTH + SOUTH_WEST + WEST
        // 8 + 16 + 32 + 64 + 128
        static const uint8_t TOP_ROW = 248;
        // WEST + NORTH_WEST + NORTH + NORTH_EAST + EAST
        // 128 + 1 + 2 + 4 + 8
        static const uint8_t BOTTOM_ROW = 143;
        // NORTH + NORTH_EAST + EAST + SOUTH_EAST + SOUTH
        // 2 + 4 + 8 + 16 + 32
        static const uint8_t LEFT_COLUMN = 62;
        // SOUTH + SOUTH_WEST + WEST + NORTH_WEST + NORTH
        // 32 + 64 + 128 + 1 + 2
        static const uint8_t RIGHT_COLUMN = 227;
        // NORTH_WEST + NORTH + NORTH_EAST + EAST + SOUTH_EAST + SOUTH + SOUTH_WEST + WEST
        // 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128
        static const uint8_t INNER = 255;
    };

}