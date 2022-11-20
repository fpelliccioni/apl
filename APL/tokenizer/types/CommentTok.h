#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;

	class CommentTok : public Token
	{
  public:
	  CommentTok(const std::wstring &raw, int spos, int epos);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<CommentTok> shared_from_this()
		{
			return std::static_pointer_cast<CommentTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
