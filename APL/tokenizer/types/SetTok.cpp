#include <APL/SetTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	SetTok::SetTok(const std::wstring &line, int spos, int epos) : APL::tokenizer::Token(line, spos, epos)
	{
	}

	std::wstring SetTok::toRepr()
	{
	  return L"←";
	}
}
