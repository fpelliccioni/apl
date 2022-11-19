#include <APL/APLMap.h>

namespace APL::types
{
	using Main = APL::Main;
	using SingleItemArr = APL::types::arrs::SingleItemArr;

	std::shared_ptr<MapPointer> APLMap::get(std::shared_ptr<Value> k)
	{
	  return std::make_shared<MapPointer>(shared_from_this(), k);
	}

	std::shared_ptr<Obj> APLMap::getRaw(const std::wstring &k)
	{
	  return getRaw(Main::toAPL(k));
	}

	std::shared_ptr<MapPointer> APLMap::get(const std::wstring &k)
	{
	  return this->operator[](Main::toAPL(k));
	}

	APLMap::MapPointer::MapPointer(std::shared_ptr<APLMap> map, std::shared_ptr<Value> k) : Settable(map->getRaw(k)), map(map), k(k)
	{
	}

	void APLMap::MapPointer::set(std::shared_ptr<Obj> v, std::shared_ptr<Callable> blame)
	{
	  map[k] = v;
	}

	std::wstring APLMap::MapPointer::toString()
	{
	  if (Main::debug)
	  {
		  return v == nullptr? L"map@" + k : L"ptr@" + k + L":" + v;
	  }
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  return v == nullptr? L"map@" + k : v->toString();
	}

	std::shared_ptr<Value> APLMap::ofShape(std::vector<int> &sh)
	{
	  return SingleItemArr::maybe(shared_from_this(), sh);
	}
}
