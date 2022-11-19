#include <APL/Settable.h>

namespace APL::types
{
	using Type = APL::Type;
	using ValueError = APL::errors::ValueError;

	Settable::Settable(std::shared_ptr<Obj> v) : v(v)
	{
	}

	APL::Type Settable::type()
	{
	  return v == nullptr? Type::var : v->type();
	}

	std::shared_ptr<Obj> Settable::get()
	{
	  if (v == nullptr)
	  {
		  throw ValueError(L"trying to get value of non-existing settable", shared_from_this());
	  }
	  return v;
	}

	std::shared_ptr<Obj> Settable::getOrThis()
	{
	  if (v == nullptr)
	  {
		  return shared_from_this();
	  }
	  return v;
	}
}
