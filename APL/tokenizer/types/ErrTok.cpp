#include <APL/ErrTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    ErrTok::ErrTok(std::string const& raw, int spos, int epos) : APL::tokenizer::Token(raw, spos, epos)
    {
    }

    ErrTok::ErrTok(std::string const& raw, int onepos) : APL::tokenizer::Token(raw, onepos, onepos + 1)
    {
    }

    std::string ErrTok::toRepr()
    {
      return L"";
    }
}
