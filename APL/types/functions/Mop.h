#pragma once

#include <APL/Callable.h>
#include <APL/Scope.h>
#include <APL/Type.h>
#include <APL/Obj.h>
#include <APL/DerivedMop.h>
#include <APL/Value.h>
#include <APL/Fun.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;

	class Mop : public Callable
	{

  protected:
	  Mop(std::shared_ptr<Scope> sc);
	  Mop();

  public:
	  Type type() override;

	  virtual std::shared_ptr<DerivedMop> derive(std::shared_ptr<Obj> aa);
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<Value> callInv(std::shared_ptr<Obj> f, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> callInvW(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> callInvA(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> under(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<Value> underW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<Value> underA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv);

	  std::wstring toString() override;
	  virtual std::wstring repr() = 0;

  protected:
	  virtual std::shared_ptr<Fun> isFn(std::shared_ptr<Obj> o);

	  // operators are equal per-object basis
  public:
	  virtual int hashCode();
	  virtual bool equals(std::shared_ptr<Obj> o);

	protected:
		std::shared_ptr<Mop> shared_from_this()
		{
			return std::static_pointer_cast<Mop>(Callable::shared_from_this());
		}
	};
}
