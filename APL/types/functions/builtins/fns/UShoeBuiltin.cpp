#include <APL/UShoeBuiltin.h>
#include <APL/Arr.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring UShoeBuiltin::repr()
	{
	  return L"∩";
	}

	std::shared_ptr<Value> UShoeBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  auto res = std::vector<std::shared_ptr<Value>>();
	  std::unordered_set<std::shared_ptr<Value>> ws(Arrays::asList(w->values()));
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
