#include <APL/StrTok.h>

namespace APL::tokenizer::types {

// using Main = APL::Main;
// using Token = APL::tokenizer::Token;
// using ChrArr = APL::types::arrs::ChrArr;

StrTok::StrTok(std::string const& line, int spos, int epos, std::string const& str)
    : APL::tokenizer::Token(line, spos, epos), val(Main::toAPL(str)), parsed(str)
{}

  std::string StrTok::toRepr() {
  return source();
}

}
