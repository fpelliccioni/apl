#include <APL/ScopeTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    ScopeTok::ScopeTok(std::string const& raw, int spos, int epos) : APL::tokenizer::Token(raw, spos, epos)
    {
    }

    std::string ScopeTok::toRepr()
    {
      return L"#";
    }
}
