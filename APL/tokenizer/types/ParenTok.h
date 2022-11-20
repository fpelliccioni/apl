#pragma once

#include <APL/tokenizer/types/LineTok.h>
#include <APL/tokenizer/types/TokArr.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::tokenizer::types
{

	using List = java::util::List;

	class ParenTok : public TokArr<std::shared_ptr<LineTok>>
	{
  public:
	  const bool hasDmd;

	  ParenTok(const std::wstring &line, int spos, int epos, std::vector<std::shared_ptr<LineTok>> &tokens, bool hasDmd);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<ParenTok> shared_from_this()
		{
			return std::static_pointer_cast<ParenTok>(TokArr::shared_from_this());
		}
	};
}
