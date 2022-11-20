#pragma once

#include <APL/Main.h>
#include <APL/tokenizer/Token.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;
	using namespace APL::types;

	class ChrTok : public Token
	{
  public:
	  const std::shared_ptr<Value> val;
	  const std::wstring parsed;

	  ChrTok(const std::wstring &line, int spos, int epos, const std::wstring &str);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<ChrTok> shared_from_this()
		{
			return std::static_pointer_cast<ChrTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
