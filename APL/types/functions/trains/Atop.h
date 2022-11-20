#pragma once

#include <APL/errors/SyntaxError.h>
#include <APL/types/Fun.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions::trains
{

	using namespace APL::types;

	class Atop : public Fun
	{
  private:
	  const std::shared_ptr<Obj> g;
	  const std::shared_ptr<Fun> h;
  public:
	  Atop(std::shared_ptr<Obj> g, std::shared_ptr<Fun> h);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	  // public Obj callInvW(Value a, Value w) {
	  //   if (!(a instanceof Value)) throw new DomainError("");
	  // }
	  std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w) override;

  private:
	  class FunAnonymousInnerClass : public Fun
	  {
	  private:
		  std::shared_ptr<Atop> outerInstance;

		  std::shared_ptr<APL::types::Obj> o;
		  std::shared_ptr<APL::types::Fun> gf;

	  public:
		  FunAnonymousInnerClass(std::shared_ptr<Atop> outerInstance, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Fun> gf);

		  std::wstring repr() override;
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass>(Fun::shared_from_this());
		  }
	  };

  public:
	  std::wstring repr() override;

	protected:
		std::shared_ptr<Atop> shared_from_this()
		{
			return std::static_pointer_cast<Atop>(Fun::shared_from_this());
		}
	};
}
