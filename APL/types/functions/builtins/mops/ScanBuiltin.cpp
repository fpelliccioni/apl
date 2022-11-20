#include <APL/ScanBuiltin.h>
#include <APL/types/Fun.h>
#include <APL/errors/NYIError.h>
#include <APL/types/Arr.h>
#include <APL/errors/DomainError.h>
#include <APL/errors/RankError.h>

namespace APL::types::functions::builtins::mops
{
	using Main = APL::Main;
	using namespace APL::errors;
	using namespace APL::types;
	using DoubleArr = APL::types::arrs::DoubleArr;
	using namespace APL::types::functions;

	std::wstring ScanBuiltin::repr()
	{
	  return L"\\";
	}

	std::shared_ptr<Value> ScanBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa);
	  // TODO ranks
	  if (w->rank != 1)
	  {
		  throw NYIError(StringHelper::wstring_to_string(L"\\: unimplemented for rank≠1 (" + Main::formatAPL(w->shape) + L" ≡ ⍴⍵)"));
	  }
	  if (w->ia == 0)
	  {
		  return w;
	  }
	  std::shared_ptr<Value> c = w[0];
	  std::vector<std::shared_ptr<Value>> res(w->ia);
	  res[0] = c;
	  for (int i = 1; i < w->ia; i++)
	  {
		c = aaf->call(c, w[i]);
		res[i] = c;
	  }
	  return Arr::create(res);
	}

	std::shared_ptr<Value> ScanBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa);
	  int n = a->asInt();
	  int len = w->ia;
	  if (n < 0)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"\\: ⍺ should be non-negative (was " + std::to_wstring(n) + L")", shared_from_this()));
	  }
	  if (w->rank > 1)
	  {
		  throw RankError(StringHelper::wstring_to_string(L"\\: rank of ⍵ should be less than 2 (was " + std::to_wstring(w->rank) + L")", shared_from_this()));
	  }

	  if (w->quickDoubleArr())
	  {
		std::vector<std::shared_ptr<Value>> res(len - n + 1);
		std::vector<double> wa = w->asDoubleArr();
		for (int i = 0; i < res.size(); i++)
		{
		  std::vector<double> curr(n);
		  std::copy_n(wa.begin() + i, n, curr.begin());
		  res[i] = aaf->call(std::make_shared<DoubleArr>(curr));
		}
		return Arr::create(res);
	  }

	  std::vector<std::shared_ptr<Value>> res(len - n + 1);
	  std::vector<std::shared_ptr<Value>> wa = w->values();
	  for (int i = 0; i < res.size(); i++)
	  {
		std::vector<std::shared_ptr<Value>> curr(n);
		// for (int j = 0; j < n; j++) curr[j] = wa[i + j];
		std::copy_n(wa.begin() + i, n, curr.begin());
		res[i] = aaf->call(Arr::create(curr));
	  }
	  return Arr::create(res);
	}
}
