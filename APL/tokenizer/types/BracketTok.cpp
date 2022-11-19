#include <APL/BracketTok.h>

namespace APL::tokenizer::types
{
	using DomainError = APL::errors::DomainError;
	using List = java::util::List;

	BracketTok::BracketTok(const std::wstring &line, int spos, int epos, std::vector<std::shared_ptr<LineTok>> &tokens, bool hasDmd) : TokArr(line, spos, tokens), array(tokens.size() >= 2 || hasDmd)
	{
	  end(epos);
	  if (tokens.empty() && hasDmd)
	  {
//JAVA TO C++ CONVERTER TODO TASK: You cannot use 'shared_from_this' in a constructor:
		  throw DomainError(L"[⋄] is not valid syntax", shared_from_this());
	  }
	}

	std::wstring BracketTok::toRepr()
	{
	  std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>(L"[");
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
	  s->append(L"]");
	  return s->toString();
	}

	std::wstring BracketTok::toString()
	{
	  return L"[...]";
	}
}
