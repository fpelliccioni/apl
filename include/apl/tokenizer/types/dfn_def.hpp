#pragma once

#include <apl/tokenizer/types/dfn.hpp>

namespace types {

dfn::dfn(std::string_view l, int spos, int epos, std::vector<line> tokens)
    : array(l, spos, tokens)
{
    end(epos);
}

std::string dfn::to_repr() const {
    std::string s = "{";
    bool tail = false;
    for (auto v : tokens) {
        if (tail) s += " ⋄ ";
        s += ::to_repr(v);
        tail = true;
    }
    s += "}";
    return s;
}

} // namespace types


// package APL.tokenizer.types;

// import java.util.List;

// public class DfnTok extends TokArr<LineTok> {

//   public DfnTok(String line, int spos, int epos, List<LineTok> tokens) {
//     super(line, spos, tokens);
//     end(epos);
//   }

//   @Override public String toRepr() {
//     StringBuilder s = new StringBuilder("{");
//     boolean tail = false;
//     for (var v : tokens) {
//       if (tail) s.append(" ⋄ ");
//       s.append(v.toRepr());
//       tail = true;
//     }
//     s.append("}");
//     return s.toString();
//   }
// }