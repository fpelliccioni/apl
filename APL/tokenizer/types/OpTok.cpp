#include <APL/OpTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    OpTok::OpTok(std::string const& line, int spos, int epos, std::string const& op) : APL::tokenizer::Token(line, spos, epos), op(op)
    {

    }

    std::string OpTok::toRepr()
    {
      return op;
    }
}
