#pragma once

#include <APL/errors/SyntaxError.h>
#include <APL/types/functions/Dop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedDop.h>
#include <APL/types/Fun.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::dops
{

	// using namespace APL::types;
	// using namespace APL::types::functions;

	class JotBuiltin : public Dop
	{
  public:
	  std::string repr() override;


	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;
	  std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w) override;
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;

	  std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> callInvA(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> under(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;

  private:
	  class FunAnonymousInnerClass : public Fun
	  {
	  private:
		  std::shared_ptr<JotBuiltin> outerInstance;

		  std::shared_ptr<APL::types::Obj> o;
		  std::shared_ptr<APL::types::Fun> gf;

	  public:
		  FunAnonymousInnerClass(std::shared_ptr<JotBuiltin> outerInstance, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Fun> gf);

		  std::string repr() override;
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass>(Fun::shared_from_this());
		  }
	  };

	protected:
		std::shared_ptr<JotBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<JotBuiltin>(Dop::shared_from_this());
		}
	};
}
