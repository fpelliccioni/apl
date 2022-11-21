#include <APL/NumTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;
    using Num = APL::types::Num;

    NumTok::NumTok(std::string const& line, int spos, int epos, double d) : APL::tokenizer::Token(line, spos, epos), num(std::make_shared<Num>(d))
    {
    }

    std::string NumTok::toTree(std::string const& p)
    {
      return p + L"num : " + num + L"\n";
    }

    std::string NumTok::toRepr()
    {
      return source();
    }
}
