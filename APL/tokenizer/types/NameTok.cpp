#include <APL/NameTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    NameTok::NameTok(std::string const& line, int spos, int epos, std::string const& name) : APL::tokenizer::Token(line, spos, epos), name(name)
    {
    }

    std::string NameTok::toTree(std::string const& p)
    {
      return p + L"name: " + name + L"\n";
    }

    std::string NameTok::toRepr()
    {
      return name;
    }
}
