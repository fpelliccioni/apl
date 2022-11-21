#include <APL/UShoeBuiltin.h>
#include <APL/types/Arr.h>

namespace APL::types::functions::builtins::fns
{
	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::string UShoeBuiltin::repr()
	{
	  return L"∩";
	}

	std::shared_ptr<APL::types::Value> UShoeBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  auto res = std::vector<std::shared_ptr<APL::types::Value>>();
	  std::unordered_set<std::shared_ptr<APL::types::Value>> ws(Arrays::asList(w->values()));
	  for (auto v : a)
	  {
		  if (std::find(ws.begin(), ws.end(), v) != ws.end())
		  {
			  res.push_back(v);
		  }
	  }
	  return Arr::create(res);
	}
}
