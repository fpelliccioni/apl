#include <APL/types/functions/builtins/fns/RShoeUBBuiltin.h>
#include <APL/types/APLMap.h>
#include <APL/types/Arr.h>
#include <APL/types/Primitive.h>
#include <APL/types/arrs/Rank0Arr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	std::wstring RShoeUBBuiltin::repr()
	{
	  return L"⊇";
	}

	RShoeUBBuiltin::RShoeUBBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
	{
	}

	std::shared_ptr<Value> RShoeUBBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return on(a, w, sc->IO, shared_from_this());
	}

	std::shared_ptr<Value> RShoeUBBuiltin::on(std::shared_ptr<Value> a, std::shared_ptr<Value> w, int IO, std::shared_ptr<Callable> blame)
	{
	  if (std::dynamic_pointer_cast<APLMap>(w) != nullptr)
	  {
		std::vector<std::shared_ptr<Value>> res(a->ia);
		std::shared_ptr<APLMap> map = std::static_pointer_cast<APLMap>(w);
		std::vector<std::shared_ptr<Value>> ks = a->values();
		for (int i = 0; i < a->ia; i++)
		{
			res[i] = std::static_pointer_cast<Value>(map->getRaw(ks[i]));
		}
		return Arr::createL(res, a->shape);
	  }
	  if (std::dynamic_pointer_cast<Primitive>(a) != nullptr && w->rank == 1)
	  {
		std::shared_ptr<Value> r = w[static_cast<int>(a->asDouble()) - IO];
		if (std::dynamic_pointer_cast<Primitive>(r) != nullptr)
		{
			return r;
		}
		else
		{
			return std::make_shared<Rank0Arr>(r);
		}
	  }

	  return on(Indexer::poss(a, w->shape, IO, blame), w);
	}

	std::shared_ptr<Value> RShoeUBBuiltin::on(std::shared_ptr<Indexer::PosSh> poss, std::shared_ptr<Value> w)
	{
	  if (w->quickDoubleArr())
	  {
		std::vector<double> res(Arr::prod(poss->sh));
		std::vector<double> wd = w->asDoubleArr();
		std::vector<int> idxs = poss->vals;
		for (int i = 0; i < idxs.size(); i++)
		{
		  res[i] = wd[idxs[i]];
		}
		return DoubleArr::safe(res, poss->sh);
	  }
	  std::vector<std::shared_ptr<Value>> res(Arr::prod(poss->sh));
	  std::vector<int> idxs = poss->vals;
	  for (int i = 0; i < idxs.size(); i++)
	  {
		res[i] = w[idxs[i]];
	  }
	  return Arr::createL(res, poss->sh);
	}

	std::shared_ptr<Value> RShoeUBBuiltin::underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(a, w)) : std::static_pointer_cast<Value>(o);
	  std::vector<std::shared_ptr<Value>> vs = w->valuesCopy();
	  for (int i = 0; i < a->ia; i++)
	  {
		vs[Indexer::fromShape(w->shape, a[i].asIntVec(), sc->IO)] = v[i];
	  }
	  return Arr::createL(vs, w->shape);
	}
}
