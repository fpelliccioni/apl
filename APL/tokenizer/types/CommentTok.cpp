#include <APL/CommentTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    CommentTok::CommentTok(std::string const& raw, int spos, int epos) : APL::tokenizer::Token(raw, spos, epos)
    {
    }

    std::string CommentTok::toRepr()
    {
      return L"";
    }
}
