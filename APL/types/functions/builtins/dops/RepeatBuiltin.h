#pragma once

#include <APL/types/functions/Dop.h>
#include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedDop.h>
#include <APL/types/Fun.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::dops
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::functions;

	class RepeatBuiltin : public Dop
	{
  public:
	  std::wstring repr() override;

	  RepeatBuiltin(std::shared_ptr<Scope> sc);
	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	  std::shared_ptr<Value> callInv(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	  std::shared_ptr<Value> callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> under(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Obj> o, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;
	  virtual std::shared_ptr<Value> repeat(std::shared_ptr<Fun> aa, int n, std::shared_ptr<Obj> o, std::shared_ptr<Value> w);

  private:
	  class FunAnonymousInnerClass : public Fun
	  {
	  private:
		  std::shared_ptr<RepeatBuiltin> outerInstance;

		  std::shared_ptr<APL::types::Fun> aa;
		  std::shared_ptr<APL::types::Obj> o;

	  public:
		  FunAnonymousInnerClass(std::shared_ptr<RepeatBuiltin> outerInstance, std::shared_ptr<APL::types::Fun> aa, std::shared_ptr<APL::types::Obj> o);

		  std::wstring repr() override;
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass>(Fun::shared_from_this());
		  }
	  };

	protected:
		std::shared_ptr<RepeatBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<RepeatBuiltin>(Dop::shared_from_this());
		}
	};
}
