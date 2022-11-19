#include <APL/SimpleIndexer.h>

namespace APL
{
	using Iterator = java::util::Iterator;

	SimpleIndexer::FunAnonymousInnerClass::FunAnonymousInnerClass(std::shared_ptr<DR> outerInstance)
	{
		this->outerInstance = outerInstance;
	}

	std::wstring SimpleIndexer::FunAnonymousInnerClass::repr()
	{
		return L"";
	}

	std::shared_ptr<Value> SimpleIndexer::FunAnonymousInnerClass::call(std::shared_ptr<Value> w)
	{
	  return std::make_shared<Num>(Double::longBitsToDouble((std::static_pointer_cast<BigValue>(UTackBuiltin::on(BigValue::TWO, w, DR::this)))->longValue()));
	}

	SimpleIndexer::FunAnonymousInnerClass2::FunAnonymousInnerClass2(std::shared_ptr<DR> outerInstance)
	{
		this->outerInstance = outerInstance;
	}

	std::wstring SimpleIndexer::FunAnonymousInnerClass2::repr()
	{
		return L"";
	}

	std::shared_ptr<Value> SimpleIndexer::FunAnonymousInnerClass2::call(std::shared_ptr<Value> w)
	{
	  return std::make_shared<Num>(Double::longBitsToDouble((std::static_pointer_cast<BigValue>(w))->longValue()));
	}

	SimpleIndexer::FunAnonymousInnerClass3::FunAnonymousInnerClass3(std::shared_ptr<DR> outerInstance)
	{
		this->outerInstance = outerInstance;
	}

	std::wstring SimpleIndexer::FunAnonymousInnerClass3::repr()
	{
		return L"";
	}

	std::shared_ptr<Value> SimpleIndexer::FunAnonymousInnerClass3::call(std::shared_ptr<Value> w)
	{
	  return std::make_shared<BitArr>(std::vector<long long>{Long::reverse(Double::doubleToRawLongBits(w->asDouble()))}, std::vector<int>{64});
	}

	SimpleIndexer::FunAnonymousInnerClass4::FunAnonymousInnerClass4(std::shared_ptr<DR> outerInstance)
	{
		this->outerInstance = outerInstance;
	}

	std::wstring SimpleIndexer::FunAnonymousInnerClass4::repr()
	{
		return L"";
	}

	std::shared_ptr<Value> SimpleIndexer::FunAnonymousInnerClass4::call(std::shared_ptr<Value> w)
	{
	  return std::make_shared<BigValue>(Double::doubleToRawLongBits(w->asDouble()));
	}

	SimpleIndexer::SimpleIndexer(std::vector<int> &shape, std::vector<int> &chosen) : shape(shape), chosen(chosen), shapeTP(std::vector<int>(len + 1)), len(shape.size())
	{
	  int p = 1;
	  shapeTP[len] = 1;
	  for (int i = len - 1; i >= 0; i--)
	  {
		p *= shape[i];
		shapeTP[i] = p;
	  }
	}

	std::shared_ptr<Iterator<int>> SimpleIndexer::iterator()
	{
	  bool empty = true;
	  for (auto i : chosen)
	  {
		if (i != 0)
		{
			empty = false;
			break;
		}
	  }
	  bool finalEmpty = empty & chosen.size() != 0;
	  //noinspection Convert2Diamond java 8
	  return std::make_shared<IteratorAnonymousInnerClass>(shared_from_this(), finalEmpty);
	}

	SimpleIndexer::IteratorAnonymousInnerClass::IteratorAnonymousInnerClass(std::shared_ptr<SimpleIndexer> outerInstance, bool finalEmpty) : outerInstance(outerInstance)
	{
		this->finalEmpty = finalEmpty;
		index = 0;
		hasNext_Conflict = !finalEmpty;
	}

	bool SimpleIndexer::IteratorAnonymousInnerClass::hasNext()
	{
	  return hasNext_Conflict;
	}

	std::optional<int> SimpleIndexer::IteratorAnonymousInnerClass::next()
	{
	  int ret = index;
	  index++;
	  int d = outerInstance->len - 1;
	  while (d != -1)
	  {
		if (index % outerInstance->shapeTP[d] == (outerInstance->chosen[d] * outerInstance->shapeTP[d + 1]) % outerInstance->shapeTP[d])
		{
		  index += (outerInstance->shape[d] - outerInstance->chosen[d]) * outerInstance->shapeTP[d + 1];
		  d--;
		}
		else
		{
			break;
		}
	  }
	  if (d == -1)
	  {
		  hasNext_Conflict = false;
	  }
	  return ret;
	}
}
