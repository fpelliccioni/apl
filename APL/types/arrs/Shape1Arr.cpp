#include <APL/Shape1Arr.h>
#include <APL/types/Char.h>
#include <APL/types/arrs/SingleItemArr.h>
#include <APL/types/Num.h>

namespace APL::types::arrs
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
const std::vector<int> Shape1Arr::SHAPE = std::vector<int>{1};

	Shape1Arr::Shape1Arr(std::shared_ptr<Value> item) : Arr(SHAPE, 1, 1), item(item)
	{
	}

	std::vector<int> Shape1Arr::asIntArrClone()
	{
	  return std::vector<int>{item->asInt()};
	}

	int Shape1Arr::asInt()
	{
	  throw DomainError(L"Using a shape 1 array as integer", shared_from_this());
	}

	std::shared_ptr<Value> Shape1Arr::get(int i)
	{
	  return item;
	}

	std::wstring Shape1Arr::asString()
	{
	  if (std::dynamic_pointer_cast<Char>(item) != nullptr)
	  {
		  return StringHelper::toString((std::static_pointer_cast<Char>(item))->chr);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Using array containing " + item->humanType(true) + L" as string", shared_from_this()));
	}

	std::shared_ptr<Value> Shape1Arr::prototype()
	{
	  return item->prototype();
	}

	std::shared_ptr<Value> Shape1Arr::safePrototype()
	{
	  return item->safePrototype();
	}

	std::shared_ptr<Value> Shape1Arr::ofShape(std::vector<int> &sh)
	{
	  return SingleItemArr::maybe(item, sh);
	}

	std::vector<std::shared_ptr<Value>> Shape1Arr::valuesCopy()
	{
	  return std::vector<std::shared_ptr<Value>>{item};
	}

	bool Shape1Arr::quickDoubleArr()
	{
	  return std::dynamic_pointer_cast<Num>(item) != nullptr;
	}

	std::vector<double> Shape1Arr::asDoubleArr()
	{
	  return std::vector<double>{(std::static_pointer_cast<Num>(item))->num};
	}
}
