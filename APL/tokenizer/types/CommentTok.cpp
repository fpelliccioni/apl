#include <APL/CommentTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	CommentTok::CommentTok(const std::wstring &raw, int spos, int epos) : APL::tokenizer::Token(raw, spos, epos)
	{
	}

	std::wstring CommentTok::toRepr()
	{
	  return L"";
	}
}
