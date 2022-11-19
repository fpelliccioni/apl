#include <APL/OpTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	OpTok::OpTok(const std::wstring &line, int spos, int epos, const std::wstring &op) : APL::tokenizer::Token(line, spos, epos), op(op)
	{

	}

	std::wstring OpTok::toRepr()
	{
	  return op;
	}
}
