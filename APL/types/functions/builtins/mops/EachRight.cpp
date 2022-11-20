#include <APL/EachRight.h>
#include <APL/types/Fun.h>
#include <APL/types/Arr.h>
#include <APL/EachBuiltin.h>

namespace APL::types::functions::builtins::mops
{
	using namespace APL::types;
	using Rank0Arr = APL::types::arrs::Rank0Arr;
	using namespace APL::types::functions;

	std::wstring EachRight::repr()
	{
	  return L"ᑈ";
	}

	std::shared_ptr<Value> EachRight::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::shared_ptr<Fun> ff = isFn(f);
	  std::vector<std::shared_ptr<Value>> n(w->ia);
	  for (int i = 0; i < n.size(); i++)
	  {
		  n[i] = ff->call(a, w[i]);
	  }
	  return Arr::createL(n, w->shape);
	}

	std::shared_ptr<Value> EachRight::underW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  return EachBuiltin::underW(isFn(aa), o, std::make_shared<Rank0Arr>(a), w, shared_from_this());
	}
}
