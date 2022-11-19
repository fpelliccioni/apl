#include <APL/DerivedSet.h>
#include <APL/Settable.h>
#include <APL/Value.h>

namespace APL::types::functions::builtins
{
	using namespace APL::types;

	DerivedSet::DerivedSet(std::shared_ptr<SetBuiltin> s, std::shared_ptr<Fun> f) : s(s), f(f)
	{
	}

	std::shared_ptr<Obj> DerivedSet::callObj(std::shared_ptr<Obj> a, std::shared_ptr<Obj> w, bool update)
	{
	  s->callObj(a, f->call(std::static_pointer_cast<Value>((std::static_pointer_cast<Settable>(a))->get()), std::static_pointer_cast<Value>(w)), update);
	  return w;
	}

	std::wstring DerivedSet::toString()
	{
	  return f->repr() + L"←";
	}
}
