#include <APL/DotBuiltin.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::dops
{
	// using namespace APL::types;
	// using namespace APL::types::functions;
	using ReduceBuiltin = APL::types::functions::builtins::mops::ReduceBuiltin;

	std::string DotBuiltin::repr()
	{
	  return L".";
	}

	std::shared_ptr<APL::types::Value> DotBuiltin::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return (std::make_shared<ReduceBuiltin>())->derive(aa)->call(wwf->call(a, w)); // TODO not lazy
	}
}
