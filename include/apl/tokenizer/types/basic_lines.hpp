#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <apl/tokenizer/types/line.hpp>
#include <apl/tokenizer/types/array.hpp>
#include <apl/tokenizer/types/base.hpp>

namespace types {

struct basic_lines : array<line> {
    basic_lines(std::string_view l, int spos, int epos, std::vector<line> tokens);

    std::string to_repr() const;

    std::string to_string() const {
        return "[...]";
    }

    std::string to_tree(std::string& p) const {
        return array::to_tree_internal(p, "basic_lines");
    }
};

} // namespace types


// package APL.tokenizer.types;

// import java.util.ArrayList;

// public class BasicLines extends TokArr<LineTok> {
//   public BasicLines(String line, int spos, int epos, ArrayList<LineTok> tokens) {
//     super(line, spos, epos, tokens);
//   }

//   @Override public String toRepr() {
//     StringBuilder s = new StringBuilder();
//     boolean tail = false;
//     for (var v : tokens) {
//       if (tail) s.append("\n");
//       s.append(v.toRepr());
//       tail = true;
//     }
//     return s.toString();
//   }
// }