#include <APL/ScopeTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	ScopeTok::ScopeTok(const std::wstring &raw, int spos, int epos) : APL::tokenizer::Token(raw, spos, epos)
	{
	}

	std::wstring ScopeTok::toRepr()
	{
	  return L"#";
	}
}
