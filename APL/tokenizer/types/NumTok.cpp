#include <APL/NumTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;
	using Num = APL::types::Num;

	NumTok::NumTok(const std::wstring &line, int spos, int epos, double d) : APL::tokenizer::Token(line, spos, epos), num(std::make_shared<Num>(d))
	{
	}

	std::wstring NumTok::toTree(const std::wstring &p)
	{
	  return p + L"num : " + num + L"\n";
	}

	std::wstring NumTok::toRepr()
	{
	  return source();
	}
}
