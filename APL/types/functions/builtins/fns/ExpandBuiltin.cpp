#include <APL/ExpandBuiltin.h>
#include <APL/errors/RankError.h>
#include <APL/errors/NYIError.h>
#include <APL/errors/DomainError.h>
#include <APL/Arr.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::errors;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring ExpandBuiltin::repr()
	{
	  return L"⍀";
	}

	std::shared_ptr<Value> ExpandBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (a->rank != 1)
	  {
		  throw RankError(L"⍀: ⍺ bust be of rank 1", shared_from_this(), a);
	  }
	  if (w->rank >= 2)
	  {
		  throw NYIError(L"⍀: rank 2 or more ⍵", shared_from_this(), w);
	  }
	  std::shared_ptr<Value> pr = nullptr;
	  std::vector<int> is = a->asIntArr(); // vectorness checked before
	  int ram = 0;
	  int iam = 0;
	  for (auto v : is)
	  {
		ram += std::max(1, std::abs(v));
		iam += v > 0? 1 : 0;
	  }
	  if (iam != w->ia)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍀: required input amount (" + std::to_wstring(iam) + L") not equal to given (" + std::to_wstring(w->ia) + L")", shared_from_this()));
	  }
	  std::vector<std::shared_ptr<Value>> res(ram);
	  int rp = 0;
	  int ip = 0;

	  for (auto v : is)
	  {
		if (v <= 0)
		{
		  if (pr->empty())
		  {
			  pr = w->safePrototype();
		  }
		  v = std::max(1, -v);
		  for (int i = 0; i < v; i++)
		  {
			  res[rp++] = pr;
		  }
		}
		else
		{
		  std::shared_ptr<Value> c = w[ip];
		  for (int i = 0; i < v; i++)
		  {
			res[rp++] = c;
		  }
		  ip++;
		}
	  }

	  return Arr::create(res);
	}
}
