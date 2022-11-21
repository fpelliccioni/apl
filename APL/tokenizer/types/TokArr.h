#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <helpers/tangible_stringbuilder.h>

namespace APL::tokenizer::types {

    using Token = APL::tokenizer::Token;

    // using List = java::util::List;

    template<typename T>
    class TokArr : public Token
    {
        using TVal = typename T::element_type;
        static_assert(std::is_base_of<APL::tokenizer::Token, TVal>::value, "T must inherit from APL::tokenizer::Token");

  public:
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: public final java.util.List<T> tokens;
      std::vector<T> tokens;

      TokArr(std::string const& line, int pos, std::vector<T> &tokens)
        : Token(line, pos), tokens(tokens)
      {}

      TokArr(std::string const& line, int spos, int epos, std::vector<T> &tokens)
        : Token(line, spos, epos), tokens(tokens)
      {}

      std::string toTree(std::string const& p) override {
        std::shared_ptr<StringBuilder> r = std::make_shared<StringBuilder>();
        r->append(p)->append(this->getClass().getCanonicalName());
        r->append(L' ')->append(spos)->append(L'-')->append(epos);
        r->append(L'\n');
        p += L"  ";
        for (auto t : tokens)
        {
            r->append(t->toTree(p));
        }
        return r->toString();
      }

    protected:
        std::shared_ptr<TokArr> shared_from_this() {
            return std::static_pointer_cast<TokArr>(APL::tokenizer::Token::shared_from_this());
        }
    };
}
