// #pragma once

// #include <string>
// #include <string_view>

// #include <apl/tokenizer/tokens/base.hpp>

// namespace tokens {

// struct chr : base {
//   chr(std::string_view line, int spos, int epos, std::string str)
//     : base(line, spos, epos)
//   {}

//   std::string to_repr() const {
//     return ":";
//   }

//   Value val;
//   std::string parsed;
// };


// } // namespace tokens

// // package APL.tokenizer.types;

// // import APL.Main;
// // import APL.tokenizer.Token;
// // import APL.types.*;

// // public class ChrTok extends Token {
// //   public final Value val;
// //   public final String parsed;

// //   public ChrTok(String line, int spos, int epos, String str) {
// //     super(line, spos, epos);
// //     parsed = str;

// //     if (str.length() == 1) val = Char.of(str.charAt(0));
// //     else val = Main.toAPL(str);
// //   }

// //   @Override public String toRepr() {
// //     return source();
// //   }
// // }