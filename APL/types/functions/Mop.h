#pragma once

#include <APL/types/Callable.h>
#include <APL/Scope.h>
#include <APL/Type.h>
#include <APL/types/Obj.h>
#include <APL/types/functions/DerivedMop.h>
#include <APL/types/Value.h>
#include <APL/types/Fun.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions
{

	// using namespace APL;
	// using namespace APL::errors;
	// using namespace APL::types;

	class Mop : public Callable
	{

  protected:
	  Mop(std::shared_ptr<Scope> sc);
	  Mop();

  public:
	  Type type() override;

	  virtual std::shared_ptr<DerivedMop> derive(std::shared_ptr<APL::types::Obj> aa);
	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w);
	  virtual std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);
	  virtual std::shared_ptr<APL::types::Value> callInvA(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);
	  virtual std::shared_ptr<APL::types::Value> under(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<APL::types::Value> underW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv);
	  virtual std::shared_ptr<APL::types::Value> underA(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv);

	  std::string toString() override;
	  virtual std::string repr() = 0;

  protected:
	  virtual std::shared_ptr<Fun> isFn(std::shared_ptr<APL::types::Obj> o);

	  // operators are equal per-object basis
  public:
	  virtual int hashCode();
	  virtual bool equals(std::shared_ptr<APL::types::Obj> o);

	protected:
		std::shared_ptr<Mop> shared_from_this()
		{
			return std::static_pointer_cast<Mop>(Callable::shared_from_this());
		}
	};
}
