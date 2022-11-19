#include <APL/DiamondTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	DiamondTok::DiamondTok(const std::wstring &raw, int pos) : APL::tokenizer::Token(raw, pos, pos + 1)
	{
	}

	std::wstring DiamondTok::toRepr()
	{
	  return L"";
	}
}
