#include <APL/ChrTok.h>
#include <APL/types/Char.h>

namespace APL::tokenizer::types {
    using Main = APL::Main;
    using Token = APL::tokenizer::Token;
    // using namespace APL::types;

    ChrTok::ChrTok(std::string const& line, int spos, int epos, std::string const& str) : APL::tokenizer::Token(line, spos, epos), parsed(str)
    {

      if (str.length() == 1)
      {
          val = Char::of(str[0]);
      }
      else
      {
          val = Main::toAPL(str);
      }
    }

    std::string ChrTok::toRepr()
    {
      return source();
    }
}
