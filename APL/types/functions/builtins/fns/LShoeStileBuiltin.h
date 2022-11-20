#pragma once

#include <APL/errors/RankError.h>
#include <APL/types/Value.h>
#include <APL/types/functions/Builtin.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <optional>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using Value = APL::types::Value;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;


	class LShoeStileBuiltin : public Builtin
	{

  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::wstring repr() override;

	protected:
		std::shared_ptr<LShoeStileBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<LShoeStileBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
