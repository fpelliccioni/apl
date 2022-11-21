#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/functions/builtins/mops/InvertBuiltin.h>
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

	class DualBuiltin : public Dop
	{
  public:
	  std::string repr() override;



	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;
	  std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;
	  std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
	  std::shared_ptr<APL::types::Value> callInvA(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

  public:
	  class BindA : public Fun
	  {
	public:
		const std::shared_ptr<APL::types::Value> a;
		const std::shared_ptr<Fun> f;
		BindA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<Fun> f);

		std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
		std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Value> w) override;

		std::string repr() override;

	  protected:
		  std::shared_ptr<BindA> shared_from_this()
		  {
			  return std::static_pointer_cast<BindA>(Fun::shared_from_this());
		  }
	  };

	protected:
		std::shared_ptr<DualBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<DualBuiltin>(Dop::shared_from_this());
		}
	};
}
