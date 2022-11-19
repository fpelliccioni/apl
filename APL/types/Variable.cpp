#include <APL/Variable.h>
#include <APL/Main.h>

namespace APL::types
{
	using namespace APL;
	using ValueError = APL::errors::ValueError;

	Variable::Variable(std::shared_ptr<Scope> sc, const std::wstring &name) : Settable(sc->get(name)), sc(sc), name(name)
	{
	}

	std::shared_ptr<Obj> Variable::get()
	{
	  if (v == nullptr)
	  {
		  throw ValueError(StringHelper::wstring_to_string(L"trying to get value of non-existing variable " + name, shared_from_this()));
	  }
	  return v;
	}

	void Variable::set(std::shared_ptr<Obj> v, std::shared_ptr<Callable> blame)
	{
	  sc->set(name, v);
	}

	void Variable::update(std::shared_ptr<Obj> v)
	{
	  sc->update(name, v);
	}

	std::wstring Variable::toString()
	{
	  if (Main::debug)
	  {
		  return v == nullptr? L"var:" + name : L"var:" + v;
	  }
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  return v == nullptr? L"var:" + name : v->toString();
	}
}
