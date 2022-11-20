#pragma once

#include <APL/Main.h>
#include <APL/tokenizer/Token.h>
#include <APL/types/arrs/ChrArr.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;
	using ChrArr = APL::types::arrs::ChrArr;

	class StrTok : public Token
	{
  public:
	  const std::shared_ptr<ChrArr> val;
	  const std::wstring parsed;

	  StrTok(const std::wstring &line, int spos, int epos, const std::wstring &str);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<StrTok> shared_from_this()
		{
			return std::static_pointer_cast<StrTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
