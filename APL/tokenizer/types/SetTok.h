#pragma once

#include <APL/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;

	class SetTok : public Token
	{
  public:
	  SetTok(const std::wstring &line, int spos, int epos);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<SetTok> shared_from_this()
		{
			return std::static_pointer_cast<SetTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
