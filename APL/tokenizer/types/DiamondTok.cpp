#include <APL/DiamondTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    DiamondTok::DiamondTok(std::string const& raw, int pos) : APL::tokenizer::Token(raw, pos, pos + 1)
    {
    }

    std::string DiamondTok::toRepr()
    {
      return L"";
    }
}
