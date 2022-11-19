#include <APL/ColonTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	ColonTok::ColonTok(const std::wstring &line, int spos, int epos) : APL::tokenizer::Token(line, spos, epos)
	{
	}

	std::wstring ColonTok::toRepr()
	{
	  return L":";
	}
}
