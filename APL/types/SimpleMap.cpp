#include <APL/SimpleMap.h>

namespace APL::types
{
	using SyntaxError = APL::errors::SyntaxError;

	std::shared_ptr<Obj> SimpleMap::getRaw(std::shared_ptr<Value> k)
	{
	  return getv(k->asString());
	}

	void SimpleMap::set(std::shared_ptr<Value> k, std::shared_ptr<Obj> v)
	{
	  setv(k->asString(), v);
	}

	std::shared_ptr<Arr> SimpleMap::allValues()
	{
	  throw SyntaxError(StringHelper::wstring_to_string(L"getting list of values of " + name()));
	}

	std::shared_ptr<Arr> SimpleMap::allKeys()
	{
	  throw SyntaxError(StringHelper::wstring_to_string(L"getting list of keys of " + name()));
	}

	std::shared_ptr<Arr> SimpleMap::kvPair()
	{
	  throw SyntaxError(StringHelper::wstring_to_string(L"getting entries of " + name()));
	}

	int SimpleMap::size()
	{
	  throw SyntaxError(StringHelper::wstring_to_string(L"getting size of " + name()));
	}
}
