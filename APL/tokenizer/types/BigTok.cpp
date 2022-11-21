#include <APL/BigTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;
    using APL::types::BigValue = APL::types::APL::types::BigValue;

    BigTok::BigTok(std::string const& line, int spos, int epos, std::shared_ptr<APL::types::BigValue> val) : APL::tokenizer::Token(line, spos, epos), val(val)
    {
    }

    std::string BigTok::toRepr()
    {
      return source();
    }
}
