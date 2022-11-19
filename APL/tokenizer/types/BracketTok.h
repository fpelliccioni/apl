#pragma once

#include <APL/errors/DomainError.h>
#include <APL/LineTok.h>
#include <APL/TokArr.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::tokenizer::types
{


	using List = java::util::List;

	class BracketTok : public TokArr<std::shared_ptr<LineTok>>
	{
  public:
	  const bool array;

	  BracketTok(const std::wstring &line, int spos, int epos, std::vector<std::shared_ptr<LineTok>> &tokens, bool hasDmd);

	  std::wstring toRepr() override;

	  virtual std::wstring toString();

	protected:
		std::shared_ptr<BracketTok> shared_from_this()
		{
			return std::static_pointer_cast<BracketTok>(TokArr::shared_from_this());
		}
	};
}
