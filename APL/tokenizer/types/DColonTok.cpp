#include <APL/DColonTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    DColonTok::DColonTok(std::string const& line, int spos, int epos) : APL::tokenizer::Token(line, spos, epos)
    {
    }

    std::string DColonTok::toRepr()
    {
      return L"::";
    }
}
