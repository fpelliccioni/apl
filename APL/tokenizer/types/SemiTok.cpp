#include <APL/SemiTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	SemiTok::SemiTok(const std::wstring &line, int spos, int epos) : APL::tokenizer::Token(line, spos, epos)
	{
	}

	std::wstring SemiTok::toRepr()
	{
	  return L";";
	}
}
