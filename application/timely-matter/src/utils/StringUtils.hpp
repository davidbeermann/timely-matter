#pragma once


namespace timelymatter {

    inline string padNumber(int num, int padding) {
        string out = "";
        int l = to_string(num).length();
        if (l < padding) {
            for (int i = 0; i < padding - l; ++i) {
                out += "0";
            }
        }
        out += to_string(num);
        return out;
    }

}