#include <APL/BigTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;
	using BigValue = APL::types::BigValue;

	BigTok::BigTok(const std::wstring &line, int spos, int epos, std::shared_ptr<BigValue> val) : APL::tokenizer::Token(line, spos, epos), val(val)
	{
	}

	std::wstring BigTok::toRepr()
	{
	  return source();
	}
}
