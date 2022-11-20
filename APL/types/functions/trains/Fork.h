#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/Fun.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions::trains
{

	using namespace APL::types;

	class Fork : public Fun
	{
  private:
	  const std::shared_ptr<Obj> f;
	  const std::shared_ptr<Fun> g, h;
  public:
	  Fork(std::shared_ptr<Obj> f, std::shared_ptr<Fun> g, std::shared_ptr<Fun> h);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::wstring repr() override;

	  std::shared_ptr<Value> under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w) override;

  private:
	  class FunAnonymousInnerClass : public Fun
	  {
	  private:
		  std::shared_ptr<Fork> outerInstance;

		  std::shared_ptr<APL::types::Obj> o;
		  std::shared_ptr<APL::types::Value> fa;

	  public:
		  FunAnonymousInnerClass(std::shared_ptr<Fork> outerInstance, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> fa);

		  std::wstring repr() override;
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass>(Fun::shared_from_this());
		  }
	  };

	protected:
		std::shared_ptr<Fork> shared_from_this()
		{
			return std::static_pointer_cast<Fork>(Fun::shared_from_this());
		}
	};
}
