#include <APL/SemiTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    SemiTok::SemiTok(std::string const& line, int spos, int epos) : APL::tokenizer::Token(line, spos, epos)
    {
    }

    std::string SemiTok::toRepr()
    {
      return L";";
    }
}
