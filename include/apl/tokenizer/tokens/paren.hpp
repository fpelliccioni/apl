#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <apl/tokenizer/tokens/line.hpp>
#include <apl/tokenizer/tokens/array.hpp>
#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct paren : array<line> {
    paren(std::string_view l, int spos, int epos, std::vector<line> tokens, bool hasDmd);

    std::string to_repr() const;

    std::string to_tree(std::string& p) const {
        return array::to_tree_internal(p, "paren");
    }

    bool hasDmd;
};

} // namespace tokens


// package APL.tokenizer.types;

// import java.util.List;

// public class ParenTok extends TokArr<LineTok> {
//   public final boolean hasDmd;

//   public ParenTok(String line, int spos, int epos, List<LineTok> tokens, boolean hasDmd) {
//     super(line, spos, tokens);
//     this.hasDmd = hasDmd;
//     end(epos);
//   }

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