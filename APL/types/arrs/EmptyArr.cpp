#include <APL/EmptyArr.h>
#include <APL/errors/DomainError.h>
#include <APL/DoubleArr.h>
#include <APL/errors/ImplementationError.h>

namespace APL::types::arrs
{
	using namespace APL::errors;
	using namespace APL::types;
	using Iterator = java::util::Iterator;
const std::vector<int> EmptyArr::SHAPE0 = std::vector<int>{0};
const std::shared_ptr<EmptyArr> EmptyArr::SHAPE0Q = std::make_shared<EmptyArr>(SHAPE0, nullptr);
const std::shared_ptr<EmptyArr> EmptyArr::SHAPE0N = std::make_shared<EmptyArr>(SHAPE0, Num::ZERO);
const std::vector<int> EmptyArr::NOINTS = std::vector<int>(0);

	EmptyArr::EmptyArr(std::vector<int> &sh, std::shared_ptr<Value> proto) : Arr(sh, 0, sh.size()), proto(proto)
	{
	}

	std::vector<int> EmptyArr::asIntArrClone()
	{
	  return NOINTS;
	}

	int EmptyArr::asInt()
	{
	  throw DomainError(L"Using empty array as integer", shared_from_this());
	}

	bool EmptyArr::quickDoubleArr()
	{
	  return true;
	}

	std::vector<double> EmptyArr::asDoubleArr()
	{
	  return DoubleArr::EMPTY;
	}

	std::shared_ptr<Value> EmptyArr::get(int i)
	{
	  throw ImplementationError(L"internal: using get() on empty array; view )stack");
	}

	std::wstring EmptyArr::asString()
	{
	  if (rank >= 2)
	  {
		  throw DomainError(L"Using rank≥2 array as char vector", shared_from_this());
	  }
	  return L"";
	}

	std::shared_ptr<Value> EmptyArr::prototype()
	{
	  if (proto->empty())
	  {
		  throw DomainError(L"couldn't get prototype", shared_from_this());
	  }
	  return proto;
	}

	std::shared_ptr<Value> EmptyArr::safePrototype()
	{
	  return proto;
	}

	std::shared_ptr<Value> EmptyArr::ofShape(std::vector<int> &sh)
	{
	  assert(ia == Arr::prod(sh));
	  return std::make_shared<EmptyArr>(sh, proto);
	}

const std::vector<std::shared_ptr<Value>> EmptyArr::NO_VALUES = std::vector<std::shared_ptr<Value>>(0);

	std::vector<std::shared_ptr<Value>> EmptyArr::valuesCopy()
	{
	  return NO_VALUES; // safe, copy or not - doesn't matter
	}

	std::shared_ptr<Value> EmptyArr::squeeze()
	{
	  return shared_from_this();
	}

const std::shared_ptr<java::util::Iterator<std::shared_ptr<Value>>> EmptyArr::EIT = std::make_shared<IteratorAnonymousInnerClass>();

	bool EmptyArr::IteratorAnonymousInnerClass::hasNext()
	{
		return false;
	}

	std::shared_ptr<Value> EmptyArr::IteratorAnonymousInnerClass::next()
	{
		throw IllegalStateException("iterating empty array");
	}

	std::shared_ptr<Iterator<std::shared_ptr<Value>>> EmptyArr::iterator()
	{
	  return EIT;
	}
}
