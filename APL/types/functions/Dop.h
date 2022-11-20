#pragma once

#include <APL/types/Callable.h>
#include <APL/Scope.h>
#include <APL/Type.h>
#include <APL/types/Obj.h>
#include <APL/types/functions/DerivedDop.h>
#include <APL/types/Value.h>
#include <APL/types/Fun.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;

	class Dop : public Callable
	{

  protected:
	  Dop(std::shared_ptr<Scope> sc);
	  Dop();

  public:
	  Type type() override;

	  virtual std::shared_ptr<DerivedDop> derive(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww);
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv);
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv);
	  virtual std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv);
	  virtual std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv);
	  virtual std::shared_ptr<Value> callInv(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> under(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Obj> o, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv);
	  virtual std::shared_ptr<Value> underW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv);
	  virtual std::shared_ptr<Value> underA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv);

	  std::wstring toString() override;
	  virtual std::wstring repr() = 0;

  protected:
	  virtual std::shared_ptr<Fun> isFn(std::shared_ptr<Obj> o, wchar_t c);

	  // operators are equal per-object basis
  public:
	  virtual int hashCode();
	  virtual bool equals(std::shared_ptr<Obj> o);

	protected:
		std::shared_ptr<Dop> shared_from_this()
		{
			return std::static_pointer_cast<Dop>(Callable::shared_from_this());
		}
	};
}
