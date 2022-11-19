#pragma once

#include <APL/Type.h>
#include <APL/errors/ValueError.h>
#include <APL/Obj.h>
#include <APL/Callable.h>
#include <memory>

namespace APL::types
{

	using Type = APL::Type;

	class Settable : public Obj
	{
  public:
	  const std::shared_ptr<Obj> v;
  protected:
	  Settable(std::shared_ptr<Obj> v);
  public:
	  Type type() override;
	  virtual void set(std::shared_ptr<Obj> v, std::shared_ptr<Callable> blame) = 0;
	  virtual std::shared_ptr<Obj> get();
	  virtual std::shared_ptr<Obj> getOrThis();

	protected:
		std::shared_ptr<Settable> shared_from_this()
		{
			return std::static_pointer_cast<Settable>(Obj::shared_from_this());
		}
	};
}
