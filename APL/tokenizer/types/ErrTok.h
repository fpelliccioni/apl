#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;

	class ErrTok : public Token
	{
  public:
	  ErrTok(const std::wstring &raw, int spos, int epos);
	  ErrTok(const std::wstring &raw, int onepos);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<ErrTok> shared_from_this()
		{
			return std::static_pointer_cast<ErrTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
