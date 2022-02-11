#pragma once

#include <optional>
#include <string_view>
#include <vector>

#include <apl/tokenizer/tokens/array.hpp>
#include <apl/tokenizer/token_fwd.hpp>

namespace tokens {

struct line : array<token> {
    line(std::string_view raw, int spos, int epos, std::vector<token> tokens);

    static
    line inherit(std::vector<token> tokens);

    static
    line inherit(token tk);

    int colonPos();
    int eguardPos();
    std::string to_repr() const;
    std::string to_tree(std::string& p) const;

private:
    std::optional<int> colonPos_;
    std::optional<int> eguardPos_;
};

} // namespace tokens
