#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("Convert2Diamond") public class DShoeBuiltin extends APL.types.functions.Builtin
	class DShoeBuiltin : public Builtin
	{
	public:
		std::string repr() override;



	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<DShoeBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<DShoeBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
