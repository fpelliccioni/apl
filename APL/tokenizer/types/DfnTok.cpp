#include <APL/DfnTok.h>

namespace APL::tokenizer::types {
    // using List = java::util::List;

    DfnTok::DfnTok(std::string const& line, int spos, int epos, std::vector<std::shared_ptr<APL::tokenizer::types::LineTok>> &tokens) : TokArr(line, spos, tokens)
    {
      end(epos);
    }

    std::string DfnTok::toRepr()
    {
      std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>(L"{");
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
      s->append(L"}");
      return s->toString();
    }
}
