#include <APL/Rank0Arr.h>
#include <APL/types/Char.h>
#include <APL/types/arrs/SingleItemArr.h>

namespace APL::types::arrs
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
const std::vector<int> Rank0Arr::SHAPE = std::vector<int>(0);

	Rank0Arr::Rank0Arr(std::shared_ptr<Value> item) : Arr(SHAPE, 1, 0), item(item)
	{
	}

	std::vector<int> Rank0Arr::asIntArrClone()
	{
	  return std::vector<int>{item->asInt()};
	}

	int Rank0Arr::asInt()
	{
	  throw DomainError(L"Using a shape 1 array as integer", shared_from_this());
	}

	std::shared_ptr<Value> Rank0Arr::get(int i)
	{
	  return item;
	}

	std::wstring Rank0Arr::asString()
	{
	  if (std::dynamic_pointer_cast<Char>(item) != nullptr)
	  {
		  return StringHelper::toString((std::static_pointer_cast<Char>(item))->chr);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Using array containing " + item->humanType(true) + L" as string", shared_from_this()));
	}

	std::shared_ptr<Value> Rank0Arr::prototype()
	{
	  return item->prototype();
	}

	std::shared_ptr<Value> Rank0Arr::safePrototype()
	{
	  return item->safePrototype();
	}

	std::shared_ptr<Value> Rank0Arr::ofShape(std::vector<int> &sh)
	{
	  return SingleItemArr::maybe(item, sh);
	}

	std::vector<std::shared_ptr<Value>> Rank0Arr::valuesCopy()
	{
	  return std::vector<std::shared_ptr<Value>>{item};
	}
}
