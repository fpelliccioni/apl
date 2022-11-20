#pragma once

#include <APL/tokenizer/Token.h>
#include <APL/tokenizer/types/TokArr.h>
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::tokenizer::types
{

	using Token = APL::tokenizer::Token;


	class LineTok : public TokArr<std::shared_ptr<Token>>
	{
  private:
//JAVA TO C++ CONVERTER NOTE: Field name conflicts with a method name of the current type:
	  std::optional<int> colonPos_Conflict;

  public:
	  LineTok(const std::wstring &raw, int spos, int epos, std::vector<std::shared_ptr<Token>> &tokens);

	  static std::shared_ptr<LineTok> inherit(std::vector<std::shared_ptr<Token>> &tokens);

	  static std::shared_ptr<LineTok> inherit(std::shared_ptr<Token> tk);

	  virtual int colonPos();
  private:
//JAVA TO C++ CONVERTER NOTE: Field name conflicts with a method name of the current type:
	  std::optional<int> eguardPos_Conflict;
  public:
	  virtual int eguardPos();

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<LineTok> shared_from_this()
		{
			return std::static_pointer_cast<LineTok>(TokArr::shared_from_this());
		}
	};
}
