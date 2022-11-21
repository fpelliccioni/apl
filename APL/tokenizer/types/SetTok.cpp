#include <APL/SetTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    SetTok::SetTok(std::string const& line, int spos, int epos) : APL::tokenizer::Token(line, spos, epos)
    {
    }

    std::string SetTok::toRepr()
    {
      return L"←";
    }
}
