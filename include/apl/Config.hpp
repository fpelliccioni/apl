#pragma once

#include <apl/types/Num.hpp>

struct Config {
    static constexpr bool quotestrings = false;
    static constexpr bool enclosePrimitives = false;
    static constexpr bool noBoxing = false;

    static std::string formatAPL(std::vector<int> ia) {
        if (ia.size() == 0) return "⍬";
        std::string r = Num.formatInt(ia[0]);
        for (int i = 1; i < ia.size(); i++) {
            r.append(" ");
            r.append(Num.formatInt(ia[i]));
        }
        return r;
    }

};