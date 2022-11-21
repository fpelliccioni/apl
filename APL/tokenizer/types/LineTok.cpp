#include <APL/tokenizer/types/LineTok.h>
#include <APL/ColonTok.h>
#include <APL/DColonTok.h>

namespace APL::tokenizer::types {
    using Token = APL::tokenizer::Token;

    APL::tokenizer::types::LineTok::APL::tokenizer::types::LineTok(std::string const& raw, int spos, int epos, std::vector<std::shared_ptr<Token>> &tokens) : TokArr(raw, spos, epos, tokens)
    {
    }

    std::shared_ptr<APL::tokenizer::types::LineTok> APL::tokenizer::types::LineTok::inherit(std::vector<std::shared_ptr<Token>> &tokens)
    {
      std::shared_ptr<Token> fst = tokens[0];
      return std::make_shared<APL::tokenizer::types::LineTok>(fst->raw, fst->spos, tokens[tokens.size() - 1]->epos, tokens);
    }

    std::shared_ptr<APL::tokenizer::types::LineTok> APL::tokenizer::types::LineTok::inherit(std::shared_ptr<Token> tk)
    {
      std::vector<std::shared_ptr<Token>> a;
      a.push_back(tk);
      return std::make_shared<APL::tokenizer::types::LineTok>(tk->raw, tk->spos, tk->epos, a);
    }

    int APL::tokenizer::types::LineTok::colonPos()
    {
      if (!colonPos_Conflict)
      {
        colonPos_Conflict = -1;
        for (int i = 0; i < tokens.size(); i++)
        {
          if (std::dynamic_pointer_cast<ColonTok>(tokens[i]) != nullptr)
          {
            colonPos_Conflict = i;
            break;
          }
        }
      }
      return colonPos_Conflict.value();
    }

    int APL::tokenizer::types::LineTok::eguardPos()
    {
      if (!eguardPos_Conflict)
      {
        eguardPos_Conflict = -1;
        for (int i = 0; i < tokens.size(); i++)
        {
          if (std::dynamic_pointer_cast<DColonTok>(tokens[i]) != nullptr)
          {
            eguardPos_Conflict = i;
            break;
          }
        }
      }
      return eguardPos_Conflict.value();
    }

    std::string APL::tokenizer::types::LineTok::toRepr()
    {
      std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>();
      bool tail = false;
      for (auto v : tokens)
      {
        if (tail)
        {
            s->append(L" ");
        }
        s->append(v->toRepr());
        tail = true;
      }
      return s->toString();
    }
}
