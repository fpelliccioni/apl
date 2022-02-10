#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <apl/tokenizer/types/line.hpp>
#include <apl/tokenizer/types/array.hpp>
#include <apl/tokenizer/types/base.hpp>

namespace types {

struct dfn : array<line> {
    dfn(std::string_view l, int spos, int epos, std::vector<line> tokens);

    std::string to_repr() const;

    std::string to_tree(std::string& p) const {
        return array::to_tree_internal(p, "dfn");
    }
};

} // namespace types
