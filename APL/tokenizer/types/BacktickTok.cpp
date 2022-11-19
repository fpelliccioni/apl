#include <APL/BacktickTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	BacktickTok::BacktickTok(const std::wstring &raw, int spos, int epos, std::shared_ptr<Token> val) : APL::tokenizer::Token(raw, spos, epos), val(LineTok::inherit(val))
	{
	}

	std::wstring BacktickTok::toRepr()
	{
	  return L"`" + val->toRepr();
	}

	std::shared_ptr<LineTok> BacktickTok::value()
	{
	  return val;
	}
}
