#pragma once

#include <APL/errors/DomainError.h>
#include <APL/mops/InvertBuiltin.h>
#include <APL/Dop.h>
#include <APL/Obj.h>
#include <APL/Value.h>
#include <APL/DerivedDop.h>
#include <APL/Fun.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::dops
{

	using namespace APL::types;
	using namespace APL::types::functions;

	class DualBuiltin : public Dop
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;
	  std::shared_ptr<Value> callInv(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;
	  std::shared_ptr<Value> callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

  public:
	  class BindA : public Fun
	  {
	public:
		const std::shared_ptr<Value> a;
		const std::shared_ptr<Fun> f;
		BindA(std::shared_ptr<Value> a, std::shared_ptr<Fun> f);

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
		std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;

		std::wstring repr() override;

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
