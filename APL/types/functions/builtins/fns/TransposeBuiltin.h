#pragma once

#include <APL/Indexer.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	class TransposeBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<TransposeBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<TransposeBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
