#pragma once

#include <APL/Token.h>
#include <APL/types/BigValue.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;
	using BigValue = APL::types::BigValue;

	class BigTok : public Token
	{
  public:
	  const std::shared_ptr<BigValue> val;
	  BigTok(const std::wstring &line, int spos, int epos, std::shared_ptr<BigValue> val);
	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<BigTok> shared_from_this()
		{
			return std::static_pointer_cast<BigTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
