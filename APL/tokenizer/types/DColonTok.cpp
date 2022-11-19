#include <APL/DColonTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	DColonTok::DColonTok(const std::wstring &line, int spos, int epos) : APL::tokenizer::Token(line, spos, epos)
	{
	}

	std::wstring DColonTok::toRepr()
	{
	  return L"::";
	}
}
