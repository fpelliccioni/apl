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

	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;


	class ReplicateBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  static std::shared_ptr<Value> replicate(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<Callable> blame);


	  std::shared_ptr<Value> underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

  private:
	  class FunAnonymousInnerClass : public Fun
	  {
	  private:
		  std::shared_ptr<ReplicateBuiltin> outerInstance;

		  std::shared_ptr<APL::types::Value> a;

	  public:
		  FunAnonymousInnerClass(std::shared_ptr<ReplicateBuiltin> outerInstance, std::shared_ptr<APL::types::Value> a);

		  std::wstring repr() override;
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

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
