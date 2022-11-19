#include <APL/RandBuiltin.h>
#include <APL/arrs/SingleItemArr.h>
#include <APL/arrs/BitArr.h>
#include <APL/arrs/DoubleArr.h>

namespace APL::types::functions::builtins::fns
{
	using Scope = APL::Scope;
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using BigInteger = java::math::BigInteger;

	std::wstring RandBuiltin::repr()
	{
	  return L"?";
	}

	RandBuiltin::RandBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
	{
	}

	std::shared_ptr<Value> RandBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> v)
	{
	  if (v->num == 0)
	  {
		  return std::make_shared<Num>(outerInstance->sc.rand(1.0));
	  }
	  else
	  {
		  return Num::of(outerInstance->sc.rand(v->asInt()) + outerInstance->sc.IO);
	  }
	}

	void RandBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < res.size(); i++)
	  {
		res[i] = a[i] == 0? outerInstance->sc.rand(1.0) : std::floor(outerInstance->sc.rand(a[i])) + outerInstance->sc.IO;
	  }
	}

	std::shared_ptr<Value> RandBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<BigValue> w)
	{
	  if (w->i->signum() == 0)
	  {
		  throw DomainError(L"?0L", w);
	  }
	  std::shared_ptr<BigInteger> n;
	  do
	  {
		n = std::make_shared<BigInteger>(w->i->bitLength(), outerInstance->sc.rnd);
	  } while (n->compareTo(w->i) >= 0);
	  return std::make_shared<BigValue>(outerInstance->sc->IO == 0? n : n->add(BigInteger::ONE));
	}

	std::shared_ptr<Value> RandBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (sc->IO == 0 && std::dynamic_pointer_cast<SingleItemArr>(w) != nullptr)
	  {
		std::shared_ptr<Value> f = w->first();
		if (std::dynamic_pointer_cast<Num>(f) != nullptr && (std::static_pointer_cast<Num>(f))->num == 2)
		{
		  std::vector<long long> ls(BitArr::sizeof_Keyword(w->ia));
		  for (int i = 0; i < ls.size(); i++)
		  {
			ls[i] = sc->randLong();
		  }
		  return std::make_shared<BitArr>(ls, w->shape);
		}
	  }
	  return numM(nf, w);
	}

	std::shared_ptr<Value> RandBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  int IO = sc->IO;
	  std::vector<int> vs(w->ia);
	  int wi = w->asInt();
	  int ai = a->asInt();
	  for (int i = 0; i < wi; i++)
	  {
		vs.push_back(i + IO);
	  }
	  Collections::shuffle(vs, sc->rnd);
	  std::vector<double> res(ai);
	  for (int i = 0; i < ai; i++)
	  {
		res[i] = vs[i];
	  }
	  return std::make_shared<DoubleArr>(res);
	}
}
