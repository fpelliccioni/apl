#include <APL/DfnTok.h>

namespace APL::tokenizer::types
{
	using List = java::util::List;

	DfnTok::DfnTok(const std::wstring &line, int spos, int epos, std::vector<std::shared_ptr<LineTok>> &tokens) : TokArr(line, spos, tokens)
	{
	  end(epos);
	}

	std::wstring DfnTok::toRepr()
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
