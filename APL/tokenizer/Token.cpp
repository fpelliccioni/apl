#include <APL/tokenizer/Token.h>

namespace APL::tokenizer
{
    using Tokenable = APL::types::Tokenable;

    Token::Token(std::string const& raw, int spos) : raw(raw), spos(spos)
    {
      epos = EPOS_DEF;
    }

    Token::Token(std::string const& raw, int spos, int epos) : raw(raw), spos(spos)
    {
      this->epos = epos;
    }

    void Token::end(int i)
    {
      assert(epos == EPOS_DEF);
      epos = i;
    }

    std::shared_ptr<Token> Token::getToken()
    {
      return shared_from_this();
    }

    std::string Token::toTree(std::string const& p)
    {
      p += L"  ";
      return p + this->getClass().getCanonicalName() + L' ' + spos + L'-' + epos + L'\n';
    }

    std::string Token::source()
    {
      return raw.substr(spos, epos - spos);
    }
}
