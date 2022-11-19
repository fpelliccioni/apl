#include <APL/SingleItemArr.h>
#include <APL/Primitive.h>
#include <APL/Char.h>
#include <APL/Num.h>

namespace APL::types::arrs
{
	using Main = APL::Main;
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using Iterator = java::util::Iterator;

	SingleItemArr::SingleItemArr(std::shared_ptr<Value> item, std::vector<int> &shape) : Arr(shape), item(item)
	{
	}

	std::shared_ptr<Value> SingleItemArr::maybe(std::shared_ptr<Value> item, std::vector<int> &sh)
	{
	  if (!Main::enclosePrimitives && sh.empty() && std::dynamic_pointer_cast<Primitive>(item) != nullptr)
	  {
		  return item;
	  }
	  return std::make_shared<SingleItemArr>(item, sh);
	}

	std::vector<int> SingleItemArr::asIntArrClone()
	{
	  int vi = item->asInt();
	  std::vector<int> a(ia);
	  for (int i = 0; i < ia; i++)
	  {
		  a[i] = vi;
	  }
	  return a;
	}

	int SingleItemArr::asInt()
	{
	  throw DomainError(L"Using array as integer", shared_from_this());
	}

	std::shared_ptr<Value> SingleItemArr::get(int i)
	{
	  return item;
	}

	std::shared_ptr<Value> SingleItemArr::first()
	{
	  return item;
	}

	std::wstring SingleItemArr::asString()
	{
	  if (rank >= 2)
	  {
		  throw DomainError(L"Using rank≥2 array as string", shared_from_this());
	  }
	  if (!(std::dynamic_pointer_cast<Char>(item) != nullptr))
	  {
		  throw DomainError(L"Using non-char array as string", shared_from_this());
	  }
	  wchar_t c = (std::static_pointer_cast<Char>(item))->chr;
	  std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>();
	  for (int i = 0; i < ia; i++)
	  {
		  s->append(c);
	  }
	  return s->toString();
	}

	std::shared_ptr<Value> SingleItemArr::prototype()
	{
	  return item->prototype();
	}

	std::shared_ptr<Value> SingleItemArr::safePrototype()
	{
	  return item->safePrototype();
	}

	std::shared_ptr<Value> SingleItemArr::ofShape(std::vector<int> &sh)
	{
	  return SingleItemArr::maybe(item, sh);
	}

	bool SingleItemArr::quickDoubleArr()
	{
	  return std::dynamic_pointer_cast<Num>(item) != nullptr;
	}

	std::vector<std::shared_ptr<Value>> SingleItemArr::valuesCopy()
	{
	  std::vector<std::shared_ptr<Value>> vs(ia);
	  for (int i = 0; i < ia; i++)
	  {
		  vs[i] = item;
	  }
	  return vs;
	}

	double SingleItemArr::sum()
	{
	  return item->asDouble() * ia;
	}

	std::vector<double> SingleItemArr::asDoubleArr()
	{
	  std::vector<double> res(ia);
	  double n = item->asDouble();
	  for (int i = 0; i < ia; i++)
	  {
		  res[i] = n;
	  }
	  return res;
	}

	std::vector<double> SingleItemArr::asDoubleArrClone()
	{
	  return asDoubleArr();
	}

	std::shared_ptr<Value> SingleItemArr::squeeze()
	{
	  std::shared_ptr<Value> ov = item->squeeze();
	  if (ov == item)
	  {
		  return shared_from_this();
	  }
	  return std::make_shared<SingleItemArr>(item, shape);
	}

	std::wstring SingleItemArr::oneliner(std::vector<int> &where)
	{
	  if (where.empty())
	  {
		std::wstring r = Main::formatAPL(shape);
		return r + L"⍴" + item->oneliner();
	  }
	  return Arr::oneliner(where);
	}

	std::shared_ptr<Iterator<std::shared_ptr<Value>>> SingleItemArr::iterator()
	{
	  //noinspection Convert2Diamond java 8
	  return std::make_shared<IteratorAnonymousInnerClass>(shared_from_this());
	}

	SingleItemArr::IteratorAnonymousInnerClass::IteratorAnonymousInnerClass(std::shared_ptr<SingleItemArr> outerInstance) : outerInstance(outerInstance)
	{
		i = 0;
	}

	bool SingleItemArr::IteratorAnonymousInnerClass::hasNext()
	{
	  return i < outerInstance->ia;
	}

	std::shared_ptr<Value> SingleItemArr::IteratorAnonymousInnerClass::next()
	{
	  i++;
	  return outerInstance->item;
	}
}
