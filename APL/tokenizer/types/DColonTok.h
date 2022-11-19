#pragma once

#include <APL/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;

	class DColonTok : public Token
	{
  public:
	  DColonTok(const std::wstring &line, int spos, int epos);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<DColonTok> shared_from_this()
		{
			return std::static_pointer_cast<DColonTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
