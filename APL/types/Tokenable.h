#pragma once

#include <APL/tokenizer/Token.h>
#include <memory>

namespace APL::types
{

	using Token = APL::tokenizer::Token;

	class Tokenable
	{
  public:
	  virtual std::shared_ptr<Token> getToken() = 0;
	};
}
