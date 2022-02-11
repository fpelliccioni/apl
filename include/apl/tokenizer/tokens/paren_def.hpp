#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <apl/tokenizer/tokens/paren.hpp>

namespace tokens {

paren::paren(std::string_view l, int spos, int epos, std::vector<line> tokens, bool hasDmd)
    : array(l, spos, tokens)
    , hasDmd(hasDmd)
{
    end(epos);
}

std::string paren::to_repr() const {
    std::string s = "(";
    bool tail = false;
    for (auto v : tokens) {
        if (tail) s += " ⋄ ";
        s += ::to_repr(v);
        tail = true;
    }
    s += ")";
    return s;
}

} // namespace tokens



// package APL.tokenizer.types;

// import java.util.List;

// public class ParenTok extends TokArr<LineTok> {
//   public final boolean hasDmd;


//   @Override public String toRepr() {
//     StringBuilder s = new StringBuilder("(");
//     boolean tail = false;
//     for (var v : tokens) {
//       if (tail) s.append(" ⋄ ");
//       s.append(v.toRepr());
//       tail = true;
//     }
//     s.append(")");
//     return s.toString();
//   }
// }