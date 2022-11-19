#pragma once

#include <APL/Indexer.h>
#include <APL/errors/RankError.h>
#include <APL/Value.h>
#include <APL/arrs/BitArr.h>
#include <APL/Builtin.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using Value = APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	class FindBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w);

	protected:
		std::shared_ptr<FindBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<FindBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
