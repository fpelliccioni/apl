#pragma once

#include <APL/tokenizer/Token.h>
#include <APL/types/Num.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;
	using Num = APL::types::Num;

	class NumTok : public Token
	{
  public:
	  const std::shared_ptr<Num> num;

	  NumTok(const std::wstring &line, int spos, int epos, double d);

	  std::wstring toTree(const std::wstring &p) override;

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<NumTok> shared_from_this()
		{
			return std::static_pointer_cast<NumTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
