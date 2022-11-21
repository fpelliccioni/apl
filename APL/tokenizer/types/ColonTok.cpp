#include <APL/ColonTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    ColonTok::ColonTok(std::string const& line, int spos, int epos) : APL::tokenizer::Token(line, spos, epos)
    {
    }

    std::string ColonTok::toRepr()
    {
      return L":";
    }
}
