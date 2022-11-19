#include <APL/DShoeBuiltin.h>
#include <APL/Arr.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring DShoeBuiltin::repr()
	{
	return L"∪";
	}

	std::shared_ptr<Value> DShoeBuiltin::call(std::shared_ptr<Value> w)
	{
	  auto res = std::make_shared<LinkedHashSet<std::shared_ptr<Value>>>(Arrays::asList(w->values()));
	  return Arr::create(res->toArray(std::vector<std::shared_ptr<Value>>(0)));
	}

	std::shared_ptr<Value> DShoeBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  auto m = std::make_shared<LinkedHashSet<std::shared_ptr<Value>>>(Arrays::asList(a->values()));
	  m->addAll(Arrays::asList(w->values()));
	  return Arr::create(m->toArray(std::vector<std::shared_ptr<Value>>(0)));
	}
}
