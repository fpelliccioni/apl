#pragma once

#include <APL/builtins/mops/TableBuiltin.h>
#include <APL/Fun.h>
#include <APL/Obj.h>
#include <APL/Mop.h>
#include <APL/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions
{

	using namespace APL::types;

	class DerivedMop : public Fun
	{
  private:
	  const std::shared_ptr<Obj> aa;
	  const std::shared_ptr<Mop> op;
  public:
	  DerivedMop(std::shared_ptr<Obj> aa, std::shared_ptr<Mop> op);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Obj> callObj(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Obj> callObj(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::wstring repr() override;

	  std::shared_ptr<Value> under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> underA(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<DerivedMop> shared_from_this()
		{
			return std::static_pointer_cast<DerivedMop>(Fun::shared_from_this());
		}
	};
}
