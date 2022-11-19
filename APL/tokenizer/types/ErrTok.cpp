#include <APL/ErrTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	ErrTok::ErrTok(const std::wstring &raw, int spos, int epos) : APL::tokenizer::Token(raw, spos, epos)
	{
	}

	ErrTok::ErrTok(const std::wstring &raw, int onepos) : APL::tokenizer::Token(raw, onepos, onepos + 1)
	{
	}

	std::wstring ErrTok::toRepr()
	{
	  return L"";
	}
}
