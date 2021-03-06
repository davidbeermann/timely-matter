#pragma once


// Define application wide constants
// http://stackoverflow.com/questions/1637332/static-const-vs-define#3835772
// http://stackoverflow.com/questions/641397/c-best-way-to-define-cross-file-constants

namespace timelymatter {
    bool const FLIPBOOK_ENABLED = false;
    // OSC should not be enabled together with flipbook option.
    // OSC also requires an active network connection.
    bool const OSC_ENABLED = false;
}

