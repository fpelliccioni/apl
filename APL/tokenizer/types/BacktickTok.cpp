#include <APL/BacktickTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    BacktickTok::BacktickTok(std::string const& raw, int spos, int epos, std::shared_ptr<Token> val) : APL::tokenizer::Token(raw, spos, epos), val(APL::tokenizer::types::LineTok::inherit(val))
    {
    }

    std::string BacktickTok::toRepr()
    {
      return L"`" + val->toRepr();
    }

    std::shared_ptr<APL::tokenizer::types::LineTok> BacktickTok::value()
    {
      return val;
    }
}
