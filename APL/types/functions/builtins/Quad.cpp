#include <APL/Quad.h>
#include <APL/Main.h>

namespace APL::types::functions::builtins
{
	using namespace APL;
	using namespace APL::types;

	Quad::Quad(std::shared_ptr<Scope> sc) : Settable(nullptr), sc(sc)
	{
	}

	void Quad::set(std::shared_ptr<Obj> v, std::shared_ptr<Callable> blame)
	{
	  sc->sys->println((Main::debug? L"[log] " : L"") + v);
	}

	std::shared_ptr<Obj> Quad::get()
	{
	  return Main::exec(sc->sys->input(), sc);
	}

	APL::Type Quad::type()
	{
	  return Type::gettable;
	}

	std::wstring Quad::toString()
	{
	  return L"⎕";
	}
}
