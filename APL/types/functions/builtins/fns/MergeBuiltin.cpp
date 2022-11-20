#include <APL/MergeBuiltin.h>
#include <APL/Main.h>
#include <APL/types/Num.h>
#include <APL/types/Arr.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL;
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using DoubleArr = APL::types::arrs::DoubleArr;
	using Builtin = APL::types::functions::Builtin;
	using Arrays = java::util::Arrays;

	MergeBuiltin::MergeBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
	{
	}

	std::shared_ptr<Value> MergeBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (w->rank != 1)
	  {
		  throw DomainError(L"%: ⍵ must be a vector", shared_from_this(), w);
	  }
	  int IO = sc->IO;
	  std::vector<int> sh = a->shape;
	  int i1 = 0;
	  bool allds = true;
	  for (auto v : w)
	  {
		if (!Arrays::equals(v->shape, sh))
		{
			throw DomainError(StringHelper::wstring_to_string(L"%: shape of item " + std::to_wstring(i1 + IO) + L" in ⍵ didn't match ⍺ (" + Main::formatAPL(sh) + L" vs " + Main::formatAPL(v->shape) + L")", shared_from_this(), w));
		}
		i1++;
		if (!v->quickDoubleArr())
		{
			allds = false;
		}
	  }
	  // if (IO==0 && a instanceof BitArr) { TODO
	  //
	  // }
	  if (allds)
	  {
		std::vector<double> ds(a->ia);
		std::vector<std::vector<double>> wds(w->ia);
		for (int i = 0; i < w->ia; i++)
		{
			wds[i] = w[i].asDoubleArr();
		}
		std::vector<double> idx = a->asDoubleArr();
		for (int i = 0; i < idx.size(); i++)
		{
		  ds[i] = wds[static_cast<int>(idx[i]) - IO][i];
		}
		if (a->rank == 0)
		{
			return std::make_shared<Num>(ds[0]);
		}
		return std::make_shared<DoubleArr>(ds, a->shape);
	  }
	  std::vector<std::shared_ptr<Value>> vs(a->ia);
	  std::vector<double> idx = a->asDoubleArr();
	  for (int i = 0; i < idx.size(); i++)
	  {
		vs[i] = w[static_cast<int>(idx[i]) - IO]->get(i);
	  }
	  return Arr::createL(vs, a->shape);
	}

	std::wstring MergeBuiltin::repr()
	{
	  return L"%";
	}
}
