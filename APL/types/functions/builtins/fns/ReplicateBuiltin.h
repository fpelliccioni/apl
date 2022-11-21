#pragma once

#include <APL/Main.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/functions/builtins/dops/AtBuiltin.h>
#include <APL/types/Value.h>
#include <APL/types/Callable.h>
#include <APL/types/Obj.h>
#include <APL/types/Fun.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;


	class ReplicateBuiltin : public Builtin
	{
  public:
	  std::string repr() override;



	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  static std::shared_ptr<APL::types::Value> replicate(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<APL::types::Callable> blame);


	  std::shared_ptr<APL::types::Value> underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

  private:
	  class FunAnonymousInnerClass : public Fun
	  {
	  private:
		  std::shared_ptr<ReplicateBuiltin> outerInstance;

		  std::shared_ptr<APL::types::APL::types::Value> a;

	  public:
		  FunAnonymousInnerClass(std::shared_ptr<ReplicateBuiltin> outerInstance, std::shared_ptr<APL::types::APL::types::Value> a);

		  std::string repr() override;
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass>(Fun::shared_from_this());
		  }
	  };

	protected:
		std::shared_ptr<ReplicateBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<ReplicateBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
