//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/types/Value.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/Num.h>
#include <APL/types/Char.h>
#include <APL/types/BigValue.h>
#include <APL/errors/RankError.h>
#include <APL/types/arrs/EmptyArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/arrs/HArr.h>
#include <APL/Main.h>
#include <APL/types/Primitive.h>
#include <APL/types/arrs/Rank0Arr.h>

namespace APL::types
{
	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types::arrs;

	Value::Value(std::vector<int> &shape) : shape(shape), rank(shape.size())
	{
	  int tia = 1;
	  for (int i = 0; i < rank; i++)
	  {
		  tia *= shape[i];
	  }
	  ia = tia;
	}

	Value::Value(std::vector<int> &shape, int ia, int rank) : shape(shape), rank(rank), ia(ia)
	{
	}

	std::vector<int> Value::asIntVec()
	{ // succeeds on rank ≤ 1
	  if (rank > 1)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"Using rank " + std::to_wstring(rank) + L" array as an integer vector", shared_from_this()));
	  }
	  return asIntArr();
	}

	std::vector<int> Value::asIntArr()
	{
	  return asIntArrClone();
	}

	bool Value::scalar()
	{
	  return rank == 0;
	}

	std::shared_ptr<Value> Value::first()
	{
	  return this->operator[](0);
	}

	int Value::compareTo(std::shared_ptr<Value> r)
	{
	  std::shared_ptr<Value> l = shared_from_this();

	  bool rA = std::dynamic_pointer_cast<Arr>(r) != nullptr;
	  bool lA = std::dynamic_pointer_cast<Arr>(l) != nullptr;

	  if (std::dynamic_pointer_cast<Num>(l) != nullptr && std::dynamic_pointer_cast<Num>(r) != nullptr)
	  {
		  return (std::static_pointer_cast<Num>(l))->compareTo(std::static_pointer_cast<Num>(r));
	  }
	  if (std::dynamic_pointer_cast<Char>(l) != nullptr && std::dynamic_pointer_cast<Char>(r) != nullptr)
	  {
		  return (std::static_pointer_cast<Char>(l))->compareTo(std::static_pointer_cast<Char>(r));
	  }
	  if (std::dynamic_pointer_cast<Num>(l) != nullptr && (std::dynamic_pointer_cast<Char>(r) != nullptr || rA))
	  {
		  return -1;
	  }
	  if ((std::dynamic_pointer_cast<Char>(l) != nullptr || lA) && std::dynamic_pointer_cast<Num>(r) != nullptr)
	  {
		  return 1;
	  }
	  if (std::dynamic_pointer_cast<BigValue>(l) != nullptr && std::dynamic_pointer_cast<BigValue>(r) != nullptr)
	  {
		  return (std::static_pointer_cast<BigValue>(l))->i->compareTo((std::static_pointer_cast<BigValue>(r))->i);
	  }
	  if (!lA && !rA)
	  {
		throw DomainError(StringHelper::wstring_to_string(L"Failed to compare " + l + L" and " + r, r));
	  }
	  if (!lA)
	  {
		  return -1;
	  }
	  if (!rA)
	  {
		  return 1;
	  }

	  if (l->rank != r->rank)
	  {
		  throw RankError(L"Expected ranks to be equal for compared elements", r);
	  }

	  if (l->rank > 1)
	  {
		  throw DomainError(L"Expected rank of compared array to be ≤ 2", l);
	  }

	  int min = std::min(l->ia, r->ia);
	  for (int i = 0; i < min; i++)
	  {
		int cr = l[i]->compareTo(r[i]);
		if (cr != 0)
		{
			return cr;
		}
	  }
	  return Integer::compare(l->ia, r->ia);
	}

	std::vector<std::optional<int>> Value::gradeUp()
	{
	  if (rank != 1)
	  {
		  throw DomainError(L"grading rank ≠ 1", shared_from_this());
	  }
	  std::vector<std::optional<int>> na(ia);

	  for (int i = 0; i < na.size(); i++)
	  {
		na[i] = i;
	  }
	  Arrays::sort(na, [&] (a, b)
	  {
	  return this->operator[](a)->compareTo(this->operator[](b));
	  });
	  return na;
	}

	std::vector<std::optional<int>> Value::gradeDown()
	{
	  if (rank != 1)
	  {
		  throw DomainError(L"grading rank ≠ 1", shared_from_this());
	  }
	  std::vector<std::optional<int>> na(ia);

	  for (int i = 0; i < na.size(); i++)
	  {
		na[i] = i;
	  }
	  Arrays::sort(na, [&] (a, b)
	  {
	  return this->operator[](b)->compareTo(this->operator[](a));
	  });
	  return na;
	}

	std::vector<int> Value::eraseDim(int place)
	{
	  std::vector<int> res(rank - 1);
	  std::copy_n(shape.begin(), place, res.begin());
	  std::copy_n(shape.begin() + place+1, rank - 1 - place, res.begin() + place);
	  return res;
	}

	APL::Type Value::type()
	{
	  return Type::array;
	}

	std::wstring Value::oneliner(std::vector<int> &where)
	{
	  return toString();
	}

	std::wstring Value::oneliner()
	{
	  return oneliner(EmptyArr::NOINTS);
	}

	std::vector<std::shared_ptr<Value>> Value::values()
	{
	  return valuesCopy();
	}

	std::vector<std::shared_ptr<Value>> Value::valuesCopy()
	{
	  std::vector<std::shared_ptr<Value>> vs(ia);
	  for (int i = 0; i < ia; i++)
	  {
		  vs[i] = this->operator[](i);
	  }
	  return vs;
	}

	std::shared_ptr<Iterator<std::shared_ptr<Value>>> Value::iterator()
	{
	  return std::make_shared<ValueIterator>(shared_from_this());
	}

	std::shared_ptr<Value> Value::ind(std::vector<std::vector<double>> &ind, int id, int IO)
	{
	  if (ind.size() != rank)
	  {
		  throw RankError(StringHelper::wstring_to_string(L"array rank was " + std::to_wstring(rank) + L", tried to get item at rank " + std::to_wstring(ind.size()), shared_from_this()));
	  }
	  int x = 0;
	  for (int i = 0; i < rank; i++)
	  {
		double c = ind[i][id];
		if (c < IO)
		{
			throw DomainError(StringHelper::wstring_to_string(L"Tried to access item at position " + std::to_wstring(c), shared_from_this()));
		}
		if (c >= shape[i] + IO)
		{
			throw DomainError(StringHelper::wstring_to_string(L"Tried to access item at position " + std::to_wstring(c) + L" while max was " + std::to_wstring(shape[i]), shared_from_this()));
		}
		x += c - IO;
		if (i != rank - 1)
		{
			x *= shape[i + 1];
		}
	  }
	  return get(x);
	}

	Value::ValueIterator::ValueIterator(std::shared_ptr<Value> outerInstance) : outerInstance(outerInstance)
	{
	}

	bool Value::ValueIterator::hasNext()
	{
	  return c < outerInstance->ia;
	}

	std::shared_ptr<Value> Value::ValueIterator::next()
	{
	  return get(c++);
	}

	std::shared_ptr<Value> Value::at(std::vector<int> &pos, int IO)
	{
	  if (pos.size() != rank)
	  {
		  throw RankError(StringHelper::wstring_to_string(L"array rank was " + std::to_wstring(rank) + L", tried to get item at rank " + std::to_wstring(pos.size()), shared_from_this()));
	  }
	  int x = 0;
	  for (int i = 0; i < rank; i++)
	  {
		if (pos[i] < IO)
		{
			throw DomainError(StringHelper::wstring_to_string(L"Tried to access item at position " + std::to_wstring(pos[i]), shared_from_this()));
		}
		if (pos[i] >= shape[i] + IO)
		{
			throw DomainError(StringHelper::wstring_to_string(L"Tried to access item at position " + std::to_wstring(pos[i]) + L" while max was " + std::to_wstring(shape[i] + IO - 1), shared_from_this()));
		}
		x += pos[i] - IO;
		if (i != rank - 1)
		{
			x *= shape[i + 1];
		}
	  }
	  return get(x);
	}

	std::shared_ptr<Value> Value::at(std::vector<int> &pos, std::shared_ptr<Value> def)
	{ // 0-indexed
	  int x = 0;
	  for (int i = 0; i < rank; i++)
	  {
		if (pos[i] < 0 || pos[i] >= shape[i])
		{
			return def;
		}
		x += pos[i];
		if (i != rank - 1)
		{
			x *= shape[i + 1];
		}
	  }
	  return get(x);
	}

	std::shared_ptr<Value> Value::simpleAt(std::vector<int> &pos)
	{
	  int x = 0;
	  for (int i = 0; i < rank; i++)
	  {
		x += pos[i];
		if (i != rank - 1)
		{
			x *= shape[i + 1];
		}
	  }
	  return get(x);
	}

	double Value::sum()
	{
	  double res = 0;
	  for (auto v : shared_from_this())
	  {
		res += v->asDouble();
	  }
	  return res;
	}

	std::vector<double> Value::asDoubleArr()
	{ // warning: also succeeds on a primitive number; don't modify
	  std::vector<double> res(ia);
	  int i = 0;
	  for (std::shared_ptr<Value> c : values())
	  {
		res[i++] = c->asDouble();
	  }
	  return res;
	}

	std::vector<double> Value::asDoubleArrClone()
	{
	  return asDoubleArr().clone();
	}

	double Value::asDouble()
	{
	  throw DomainError(StringHelper::wstring_to_string(L"Using " + this->humanType(true) + L" as a number", shared_from_this()));
	}

	bool Value::quickDoubleArr()
	{ // if true, asDoubleArr must succeed; warning: also succeeds on a primitive number
	  return false;
	}

	std::shared_ptr<Value> Value::squeeze()
	{
	  if (ia == 0)
	  {
		  return shared_from_this();
	  }
	  std::shared_ptr<Value> f = this->operator[](0);
	  if (std::dynamic_pointer_cast<Num>(f) != nullptr)
	  {
		std::vector<double> ds(ia);
		for (int i = 0; i < ia; i++)
		{
		  if (std::dynamic_pointer_cast<Num>(this->operator[](i)) != nullptr)
		  {
			  ds[i] = this->operator[](i).asDouble();
		  }
		  else
		  {
			ds = std::vector<double>();
			break;
		  }
		}
		if (!ds.empty())
		{
			return std::make_shared<DoubleArr>(ds, shape);
		}
	  }
	  if (std::dynamic_pointer_cast<Char>(f) != nullptr)
	  {
		std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>();
		for (int i = 0; i < ia; i++)
		{
		  if (std::dynamic_pointer_cast<Char>(this->operator[](i)) != nullptr)
		  {
			  s->append((std::static_pointer_cast<Char>(this->operator[](i)))->chr);
		  }
		  else
		  {
			s = nullptr;
			break;
		  }
		}
		if (s != nullptr)
		{
			return std::make_shared<ChrArr>(s->toString(), shape);
		}
	  }
	  bool anyBetter = false;
	  std::vector<std::shared_ptr<Value>> optimized(ia);
	  std::vector<std::shared_ptr<Value>> values = values();
	  for (int i = 0, valuesLength = values.size(); i < valuesLength; i++)
	  {
		std::shared_ptr<Value> v = values[i];
		std::shared_ptr<Value> vo = v->squeeze();
		if (vo != v)
		{
			anyBetter = true;
		}
		optimized[i] = vo;
	  }
	  if (anyBetter)
	  {
		  return std::make_shared<HArr>(optimized, shape);
	  }
	  return shared_from_this();
	}

	std::shared_ptr<Value> Value::cut(int s, int len, std::vector<int> &sh)
	{
	  if (len == 1)
	  {
		std::shared_ptr<Value> v = this->operator[](s);
		return !Main::enclosePrimitives && std::dynamic_pointer_cast<Primitive>(v) != nullptr? v : std::make_shared<Rank0Arr>(v);
	  }
	  if (quickDoubleArr())
	  {
		std::vector<double> w = asDoubleArr();
		std::vector<double> r(len);
		std::copy_n(w.begin() + s, len, r.begin());
		return std::make_shared<DoubleArr>(r, sh);
	  }
	  std::vector<std::shared_ptr<Value>> w = values();
	  std::vector<std::shared_ptr<Value>> r(len);
	  std::copy_n(w.begin() + s, len, r.begin());
	  return std::make_shared<HArr>(r, sh);
	}
}
