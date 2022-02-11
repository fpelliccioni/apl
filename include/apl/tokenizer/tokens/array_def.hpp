#pragma once

// #include <format>
#include <string_view>
#include <vector>

#include <apl/tokenizer/tokens/array.hpp>

namespace tokens {

template <typename T>
std::string array<T>::to_tree_internal(std::string& p, std::string_view class_name) const {
    // class_name: this.getClass().getCanonicalName()
    // auto r = std::format("{}{} {}-{}\n", p, class_name, spos, epos);
    std::string r = p;
    r.append(class_name);
    r += " " + std::to_string(spos) + "-" + std::to_string(epos) + '\n';

    p += "  ";
    for (auto t : tokens) {
        r += to_tree(t, p);
    }
    return r;
}

} // namespace tokens
