#include <APL/CRepeatBuiltin.h>
#include <APL/types/Fun.h>
#include <APL/Main.h>
#include <APL/types/Arr.h>

namespace APL::types::functions::builtins::dops
{
	// using namespace APL;
	// using namespace APL::types;
	// using namespace APL::types::functions;
	// using ArrayList = java::util::ArrayList;

	std::string CRepeatBuiltin::repr()
	{
	  return L"⍡";
	}

	CRepeatBuiltin::CRepeatBuiltin(std::shared_ptr<Scope> sc) : Dop(sc)
	{
	}

	std::shared_ptr<APL::types::Value> CRepeatBuiltin::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  if (std::dynamic_pointer_cast<Fun>(ww) != nullptr)
	  {
		std::vector<std::shared_ptr<APL::types::Value>> res;
		std::shared_ptr<APL::types::Value> prev = w;
		res.push_back(prev);

		std::shared_ptr<APL::types::Value> next = aaf->call(prev);
		res.push_back(next);
		std::shared_ptr<Fun> wwf = std::static_pointer_cast<Fun>(ww);
		while (!Main::bool_Keyword(wwf->call(prev, next)))
		{
		  prev = next;
		  next = aaf->call(prev);
		  res.push_back(next);
		}
		return Arr::create(res);
	  }
	  else
	  {
		int n = (std::static_pointer_cast<APL::types::Value>(ww))->asInt();
		std::vector<std::shared_ptr<APL::types::Value>> res(n);
		std::shared_ptr<APL::types::Value> curr = w;
		for (int i = 0; i < n; i++)
		{
		  curr = aaf->call(curr);
		  res[i] = curr;
		}
		return Arr::create(res);
	  }
	}
}
