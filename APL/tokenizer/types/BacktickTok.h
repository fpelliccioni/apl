#pragma once

#include <APL/Token.h>
#include <APL/LineTok.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;

	class BacktickTok : public Token
	{
  private:
	  const std::shared_ptr<LineTok> val;

  public:
	  BacktickTok(const std::wstring &raw, int spos, int epos, std::shared_ptr<Token> val);

	  std::wstring toRepr() override;

	  virtual std::shared_ptr<LineTok> value();

	protected:
		std::shared_ptr<BacktickTok> shared_from_this()
		{
			return std::static_pointer_cast<BacktickTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
