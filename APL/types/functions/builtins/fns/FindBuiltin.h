#pragma once

#include <APL/Indexer.h>
#include <APL/errors/RankError.h>
#include <APL/types/Value.h>
#include <APL/types/arrs/BitArr.h>
#include <APL/types/functions/Builtin.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using APL::types::Value = APL::types::APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	class FindBuiltin : public Builtin
	{
  public:
	  std::string repr() override;



	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);

	protected:
		std::shared_ptr<FindBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<FindBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
