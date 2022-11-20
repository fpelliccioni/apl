#include <APL/RShoeBuiltin.h>
#include <APL/types/Primitive.h>
#include <APL/types/APLMap.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Num.h>
#include <APL/errors/RankError.h>
#include <APL/errors/LengthError.h>
#include <APL/Main.h>
#include <APL/types/Arr.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;

	std::wstring RShoeBuiltin::repr()
	{
	  return L"⊃";
	}

	RShoeBuiltin::RShoeBuiltin(std::shared_ptr<Scope> sc) : Fun(sc)
	{
	}

	std::shared_ptr<Value> RShoeBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
	  {
		  return w;
	  }
	  else if (w->ia == 0)
	  {
		  return w->prototype();
	  }
	  else
	  {
		  return w->first();
	  }
	}

	std::shared_ptr<Value> RShoeBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Obj> o = callObj(a, w);
	  if (std::dynamic_pointer_cast<Value>(o) != nullptr)
	  {
		  return std::static_pointer_cast<Value>(o);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Was expected to give array, got " + o->humanType(true), shared_from_this()));
	}

	std::shared_ptr<Obj> RShoeBuiltin::callObj(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<APLMap>(w) != nullptr)
	  {
		std::shared_ptr<APLMap> map = std::static_pointer_cast<APLMap>(w);
		return map->getRaw(a);
	  }
	  if (std::dynamic_pointer_cast<Num>(a) != nullptr)
	  {
		if (w->rank != 1)
		{
			throw RankError(StringHelper::wstring_to_string(L"array rank was " + std::to_wstring(w->rank) + L", tried to get item at rank 0", shared_from_this(), w));
		}
		if (w->ia == 0)
		{
			throw LengthError(L"⊃ on array with 0 elements", shared_from_this(), w);
		}
		int p = a->asInt() - sc->IO;
		if (p >= w->ia)
		{
			throw DomainError(StringHelper::wstring_to_string(L"Tried to access item at position " + a + L" while shape was " + Main::formatAPL(w->shape), shared_from_this()));
		}
		return w[p];
	  }
	  return w->at(a->asIntVec(), sc->IO);
	}

	std::shared_ptr<Value> RShoeBuiltin::under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w)
	{
	  std::vector<std::shared_ptr<Value>> vs = w->valuesCopy();
	  vs[0] = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(w)) : std::static_pointer_cast<Value>(o);
	  return Arr::createL(vs, w->shape);
	}

	std::shared_ptr<Value> RShoeBuiltin::underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(a, w)) : std::static_pointer_cast<Value>(o);
	  if (std::dynamic_pointer_cast<Primitive>(a) != nullptr)
	  {
		std::vector<std::shared_ptr<Value>> vs = w->valuesCopy();
		vs[a->asInt() - sc->IO] = v;
		return Arr::createL(vs, w->shape);
	  }
	  else
	  {
		std::vector<std::shared_ptr<Value>> vs = w->valuesCopy();
		std::vector<int> is = a->asIntVec();
		replace(vs, v, is, 0);
		return Arr::createL(vs, w->shape);
	  }
	}

	void RShoeBuiltin::replace(std::vector<std::shared_ptr<Value>> &vs, std::shared_ptr<Value> w, std::vector<int> &d, int i)
	{
	  int c = d[i] - sc->IO;
	  if (i + 1 == d.size())
	  {
		  vs[c] = w;
	  }
	  else
	  {
		std::shared_ptr<Value> cv = vs[c];
		std::vector<std::shared_ptr<Value>> vsN = cv->valuesCopy();
		replace(vsN, w, d, i + 1);
		vs[c] = Arr::createL(vsN, cv->shape);
	  }
	}
}
