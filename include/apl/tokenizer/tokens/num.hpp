#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct num : base {
    num(std::string_view line, int spos, int epos, double d)
        : base(line, spos, epos)
        , number(d)
    {}

    std::string to_tree(std::string& p) {
        return p + "num : " + std::to_string(number) + "\n";
    }

    std::string to_repr() const {
       return std::string(source());
    }

    // Num number;
    double number;
};


} // namespace tokens

// package APL.tokenizer.types;

// import APL.tokenizer.Token;
// import APL.types.Num;

// public class NumTok extends Token {
//   public final Num num;

//   public NumTok(String line, int spos, int epos, double d) {
//     super(line, spos, epos);
//     this.num = new Num(d);
//   }

//   @Override public String toTree(String p) {
//     return p+"num : " + num + "\n";
//   }

//   @Override public String toRepr() {
//     return source();
//   }
// }