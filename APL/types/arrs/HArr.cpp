#include <APL/HArr.h>
#include <APL/types/Char.h>
#include <APL/types/Primitive.h>

namespace APL::types::arrs
{
	using Main = APL::Main;
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;

	HArr::HArr(std::vector<std::shared_ptr<Value>> &v, std::vector<int> &sh) : Arr(sh, v.size(), sh.size()), arr(v)
	{
	}

	HArr::HArr(std::vector<std::shared_ptr<Value>> &v) : Arr(std::vector<int>{v.size()}), arr(v.toArray(std::vector<std::shared_ptr<Value>>(0)))
	{ // 1D
	}

	HArr::HArr(std::vector<std::shared_ptr<Value>> &v) : Arr(std::vector<int>{v.size()}, v.size(), 1), arr(v)
	{ // 1D
	}

	HArr::HArr(std::vector<std::shared_ptr<Value>> &v, std::vector<int> &sh) : Arr(sh), arr(v.toArray(std::vector<std::shared_ptr<Value>>(0)))
	{
	}

	std::vector<int> HArr::asIntArrClone()
	{
	  std::vector<int> res(ia);
	  for (int i = 0; i < arr.size(); i++)
	  {
		res[i] = arr[i]->asInt();
	  }
	  return res;
	}

	int HArr::asInt()
	{
	  if (rank == 0)
	  {
		  return arr[0]->asInt();
	  }
	  throw DomainError(L"Using array as integer", shared_from_this());
	}

	std::shared_ptr<Value> HArr::get(int i)
	{
	  return arr[i];
	}

	bool HArr::equals(std::shared_ptr<Obj> o)
	{
	  if (!(std::dynamic_pointer_cast<Value>(o) != nullptr))
	  {
		  return false;
	  }
	  std::shared_ptr<Value> v = std::static_pointer_cast<Value>(o);
	  if (!Arrays::equals(shape, v->shape))
	  {
		  return false;
	  }
	  assert(ia == v->ia);
	  for (int i = 0; i < ia; i++)
	  {
		if (!arr[i]->equals(v[i]))
		{
			return false;
		}
	  }
	  return true;
	}

	std::wstring HArr::asString()
	{
	  std::shared_ptr<StringBuilder> r = std::make_shared<StringBuilder>(ia);
	  for (auto v : arr)
	  {
		if (!(std::dynamic_pointer_cast<Char>(v) != nullptr))
		{
			throw DomainError(StringHelper::wstring_to_string(L"Using array containing " + v->humanType(true) + L" as string", shared_from_this()));
		}
		r->append((std::static_pointer_cast<Char>(v))->chr);
	  }
	  return r->toString();
	}

	std::shared_ptr<Value> HArr::prototype()
	{
	  if (ia == 0)
	  {
		  throw DomainError(L"failed to get prototype", shared_from_this());
	  }
	  return arr[0]->prototype();
	}

	std::shared_ptr<Value> HArr::safePrototype()
	{
	  if (ia == 0)
	  {
		  return nullptr;
	  }
	  return arr[0]->safePrototype();
	}

	std::vector<std::shared_ptr<Value>> HArr::values()
	{
	  return arr;
	}

	std::vector<std::shared_ptr<Value>> HArr::valuesCopy()
	{
	  return arr.clone();
	}

	std::shared_ptr<Value> HArr::ofShape(std::vector<int> &sh)
	{
	  if (sh.empty() && Main::enclosePrimitives && std::dynamic_pointer_cast<Primitive>(arr[0]) != nullptr)
	  {
		  return arr[0];
	  }
	  return std::make_shared<HArr>(arr, sh);
	}
}
