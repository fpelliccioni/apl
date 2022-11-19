#pragma once

#include <APL/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;

	class ColonTok : public Token
	{
  public:
	  ColonTok(const std::wstring &line, int spos, int epos);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<ColonTok> shared_from_this()
		{
			return std::static_pointer_cast<ColonTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
