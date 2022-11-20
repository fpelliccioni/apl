#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;

	class NameTok : public Token
	{
  public:
	  const std::wstring name;

	  NameTok(const std::wstring &line, int spos, int epos, const std::wstring &name);

	  std::wstring toTree(const std::wstring &p) override;

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<NameTok> shared_from_this()
		{
			return std::static_pointer_cast<NameTok>(APL::tokenizer::Token::shared_from_this());
		}
	};
}
