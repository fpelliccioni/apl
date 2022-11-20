#pragma once

#include <APL/types/Fun.h>
#include <APL/types/Obj.h>
#include <APL/types/functions/Dop.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions
{

	using namespace APL::types;

	class DerivedDop : public Fun
	{
  private:
	  const std::shared_ptr<Obj> aa, ww;
	  const std::shared_ptr<Dop> op;
  public:
	  DerivedDop(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Dop> op);

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
		std::shared_ptr<DerivedDop> shared_from_this()
		{
			return std::static_pointer_cast<DerivedDop>(Fun::shared_from_this());
		}
	};
}
