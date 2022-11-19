#pragma once

#include <APL/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;

	class ScopeTok : public Token
	{
  public:
	  ScopeTok(const std::wstring &raw, int spos, int epos);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<ScopeTok> shared_from_this()
		{
			return std::static_pointer_cast<ScopeTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
