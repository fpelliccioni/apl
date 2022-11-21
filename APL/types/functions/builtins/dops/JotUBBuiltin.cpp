#include <APL/JotUBBuiltin.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::dops
{
	// using namespace APL::types;
	// using namespace APL::types::functions;

	std::string JotUBBuiltin::repr()
	{
	  return L"⍛";
	}

	std::shared_ptr<APL::types::Value> JotUBBuiltin::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->call(aaf->call(a), w);
	}

	std::shared_ptr<APL::types::Value> JotUBBuiltin::callInvW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->callInvW(aaf->call(a), w);
	}

	std::shared_ptr<APL::types::Value> JotUBBuiltin::callInvA(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return aaf->callInv(wwf->callInvA(a, w));
	}
}
