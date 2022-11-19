#include <APL/NameTok.h>

namespace APL::tokenizer::types
{
	using Token = APL::tokenizer::Token;

	NameTok::NameTok(const std::wstring &line, int spos, int epos, const std::wstring &name) : APL::tokenizer::Token(line, spos, epos), name(name)
	{
	}

	std::wstring NameTok::toTree(const std::wstring &p)
	{
	  return p + L"name: " + name + L"\n";
	}

	std::wstring NameTok::toRepr()
	{
	  return name;
	}
}
