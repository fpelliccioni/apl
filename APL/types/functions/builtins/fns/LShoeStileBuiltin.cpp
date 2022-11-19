#include <APL/LShoeStileBuiltin.h>
#include <APL/arrs/DoubleArr.h>
#include <APL/arrs/BitArr.h>

namespace APL::types::functions::builtins::fns
{
	using RankError = APL::errors::RankError;
	using Value = APL::types::Value;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	std::shared_ptr<Value> LShoeStileBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::unordered_map<std::shared_ptr<Value>, int> counts;
	  for (auto ca : a)
	  {
		  counts.emplace(ca, 0);
	  }
	  for (auto cw : w)
	  {
		std::optional<int> pv = counts[cw];
		if (pv)
		{
			counts.emplace(cw, pv.value() + 1);
		}
	  }
	  std::vector<double> res(a->ia);
	  int i = 0;
	  for (auto ca : a)
	  {
		res[i] = counts[ca];
		i++;
	  }
	  return DoubleArr::safe(res, a->shape);
	}

	std::shared_ptr<Value> LShoeStileBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (w->rank != 1)
	  {
		  throw RankError(L"⍧: rank of argument must be 1", shared_from_this(), w);
	  }
	  std::unordered_set<std::shared_ptr<Value>> encountered;
	  std::shared_ptr<BitArr::BA> res = std::make_shared<BitArr::BA>(w->shape);
	  for (auto cv : w)
	  {
		if (std::find(encountered.begin(), encountered.end(), cv) != encountered.end())
		{
			res->add(false);
		}
		else
		{
		  encountered.insert(cv);
		  res->add(true);
		}
	  }
	  return res->finish();
	}

	std::wstring LShoeStileBuiltin::repr()
	{
	  return L"⍧";
	}
}
