#include <APL/StrTok.h>

namespace APL::tokenizer::types
{
	using Main = APL::Main;
	using Token = APL::tokenizer::Token;
	using ChrArr = APL::types::arrs::ChrArr;

	StrTok::StrTok(const std::wstring &line, int spos, int epos, const std::wstring &str) : APL::tokenizer::Token(line, spos, epos), val(Main::toAPL(str)), parsed(str)
	{
	}

	std::wstring StrTok::toRepr()
	{
	  return source();
	}
}
