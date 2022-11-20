#include <APL/tokenizer/types/BasicLines.h>

namespace APL::tokenizer::types
{
	using ArrayList = java::util::ArrayList;

	BasicLines::BasicLines(const std::wstring &line, int spos, int epos, std::vector<std::shared_ptr<LineTok>> &tokens) : TokArr(line, spos, epos, tokens)
	{
	}

	std::wstring BasicLines::toRepr()
	{
	  std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>();
	  bool tail = false;
	  for (auto v : tokens)
	  {
		if (tail)
		{
			s->append(L"\n");
		}
		s->append(v->toRepr());
		tail = true;
	  }
	  return s->toString();
	}
}
