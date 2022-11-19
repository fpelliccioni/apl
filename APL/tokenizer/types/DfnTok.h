#pragma once

#include <APL/LineTok.h>
#include <APL/TokArr.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::tokenizer::types
{

	using List = java::util::List;

	class DfnTok : public TokArr<std::shared_ptr<LineTok>>
	{

  public:
	  DfnTok(const std::wstring &line, int spos, int epos, std::vector<std::shared_ptr<LineTok>> &tokens);

	  std::wstring toRepr() override;

	protected:
		std::shared_ptr<DfnTok> shared_from_this()
		{
			return std::static_pointer_cast<DfnTok>(TokArr::shared_from_this());
		}
	};
}
