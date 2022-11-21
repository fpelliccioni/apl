#include <APL/LShoeStileBuiltin.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/arrs/BitArr.h>

namespace APL::types::functions::builtins::fns
{
	using RankError = APL::errors::RankError;
	using APL::types::Value = APL::types::APL::types::Value;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	std::shared_ptr<APL::types::Value> LShoeStileBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::unordered_map<std::shared_ptr<APL::types::Value>, int> counts;
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

	std::shared_ptr<APL::types::Value> LShoeStileBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  if (w->rank != 1)
	  {
		  throw RankError(L"⍧: rank of argument must be 1", shared_from_this(), w);
	  }
	  std::unordered_set<std::shared_ptr<APL::types::Value>> encountered;
	  std::shared_ptr<APL::types::arrs::BitArr::BA> res = std::make_shared<APL::types::arrs::BitArr::BA>(w->shape);
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

	std::string LShoeStileBuiltin::repr()
	{
	  return L"⍧";
	}
}
