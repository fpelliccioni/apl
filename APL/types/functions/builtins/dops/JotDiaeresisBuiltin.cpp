#include <APL/JotDiaeresisBuiltin.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::dops
{
	// using namespace APL::types;
	// using namespace APL::types::functions;

	std::string JotDiaeresisBuiltin::repr()
	{
	  return L"⍤";
	}

	std::shared_ptr<APL::types::Value> JotDiaeresisBuiltin::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return aaf->call(wwf->call(a, w));
	}

	std::shared_ptr<APL::types::Value> JotDiaeresisBuiltin::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return aaf->call(wwf->call(w));
	}

	std::shared_ptr<APL::types::Value> JotDiaeresisBuiltin::callInv(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return aaf->call(wwf->call(w));
	}

	std::shared_ptr<APL::types::Value> JotDiaeresisBuiltin::callInvW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->callInvW(a, aaf->callInv(w));
	}

	std::shared_ptr<APL::types::Value> JotDiaeresisBuiltin::callInvA(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->callInvA(aaf->callInv(a), w);
	}
}
