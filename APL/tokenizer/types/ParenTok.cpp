#include <APL/ParenTok.h>

namespace APL::tokenizer::types {
    // using List = java::util::List;

    ParenTok::ParenTok(std::string const& line, int spos, int epos, std::vector<std::shared_ptr<APL::tokenizer::types::LineTok>> &tokens, bool hasDmd) : TokArr(line, spos, tokens), hasDmd(hasDmd)
    {
      end(epos);
    }

    std::string ParenTok::toRepr()
    {
      std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>(L"(");
      bool tail = false;
      for (auto v : tokens)
      {
        if (tail)
        {
            s->append(L" ⋄ ");
        }
        s->append(v->toRepr());
        tail = true;
      }
      s->append(L")");
      return s->toString();
    }
}
