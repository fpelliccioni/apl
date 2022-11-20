#include <APL/types/functions/builtins/dops/AtBuiltin.h>
#include <APL/types/Fun.h>
#include <APL/Main.h>
#include <APL/types/Arr.h>
#include <APL/types/Num.h>

namespace APL::types::functions::builtins::dops
{
	using namespace APL;
	using namespace APL::types;
	using DoubleArr = APL::types::arrs::DoubleArr;
	using namespace APL::types::functions;
	using RShoeUBBuiltin = APL::types::functions::builtins::fns::RShoeUBBuiltin;

	std::wstring AtBuiltin::repr()
	{
	  return L"@";
	}

	AtBuiltin::AtBuiltin(std::shared_ptr<Scope> sc) : Dop(sc)
	{
	}

	std::shared_ptr<Value> AtBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  return at(aa, ww, w, sc->IO, shared_from_this());
	}

	std::shared_ptr<Value> AtBuiltin::at(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, int IO, std::shared_ptr<Callable> blame)
	{
	  int ia = w->ia;
	  if (std::dynamic_pointer_cast<Fun>(ww) != nullptr)
	  {
		std::shared_ptr<Value> vba = (std::static_pointer_cast<Fun>(ww))->call(w);
		std::vector<bool> ba(ia);
		int matchingCount = 0;
		for (int i = 0; i < ia; i++)
		{
		  ba[i] = Main::bool_Keyword(vba[i]);
		  if (ba[i])
		  {
			  matchingCount++;
		  }
		}
		std::shared_ptr<Value> aaa;
		if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
		{
		  std::vector<std::shared_ptr<Value>> matching(matchingCount);
		  int ptr = 0;
		  for (int i = 0; i < ia; i++)
		  {
			if (ba[i])
			{
				matching[ptr++] = w[i];
			}
		  }
		  aaa = (std::static_pointer_cast<Fun>(aa))->call(Arr::create(matching));
		}
		else
		{
			aaa = std::static_pointer_cast<Value>(aa);
		}
		std::vector<std::shared_ptr<Value>> ra(ia);
		if (aaa->rank == 0)
		{
		  std::shared_ptr<Value> inner = aaa[0];
		  for (int i = 0; i < ia; i++)
		  {
			if (ba[i])
			{
				ra[i] = inner;
			}
			else
			{
				ra[i] = w[i];
			}
		  }
		}
		else
		{
		  int ptr = 0;
		  for (int i = 0; i < ia; i++)
		  {
			if (ba[i])
			{
				ra[i] = aaa[ptr++];
			}
			else
			{
				ra[i] = w[i];
			}
		  }
		}
		return Arr::createL(ra, w->shape);
	  }
	  else
	  {
		std::shared_ptr<Value> wwa = std::static_pointer_cast<Value>(ww);

		std::shared_ptr<Indexer::PosSh> poss = Indexer::poss(wwa, w->shape, IO, blame);
		std::shared_ptr<Value> repl;
		if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
		{
		  std::shared_ptr<Fun> aaf = (std::static_pointer_cast<Fun>(aa));
		  std::shared_ptr<Value> arg = RShoeUBBuiltin::on(poss, w);
		  repl = aaf->call(arg);
		}
		else
		{
		  repl = std::static_pointer_cast<Value>(aa);
		}
		return with(w, poss, repl, blame);
	  }
	}

	std::shared_ptr<Value> AtBuiltin::with(std::shared_ptr<Value> o, std::shared_ptr<Indexer::PosSh> poss, std::shared_ptr<Value> n, std::shared_ptr<Callable> blame)
	{
	  if (o->quickDoubleArr() && n->quickDoubleArr())
	  {
		std::vector<double> res = o->asDoubleArrClone();
		std::vector<int> is = poss->vals;
		if (n->rank == 0)
		{
		  double aafst = n->first()->asDouble();
		  // noinspection ForLoopReplaceableByForEach
		  for (int i = 0; i < is.size(); i++)
		  {
			  res[is[i]] = aafst;
		  }
		}
		else
		{
		  std::vector<double> nd = n->asDoubleArr();
		  Arr::eqShapes(n->shape, poss->sh, blame);
		  for (int i = 0; i < is.size(); i++)
		  {
			  res[is[i]] = nd[i];
		  }
		}
		return o->rank == 0? Num::of(res[0]) : std::make_shared<DoubleArr>(res, o->shape);
	  }
	  std::vector<std::shared_ptr<Value>> res = o->valuesCopy();
	  std::vector<int> is = poss->vals;
	  if (n->rank == 0)
	  {
		std::shared_ptr<Value> aafst = n->first();
		// noinspection ForLoopReplaceableByForEach
		for (int i = 0; i < is.size(); i++)
		{
			res[is[i]] = aafst;
		}
	  }
	  else
	  {
		Arr::eqShapes(n->shape, poss->sh, blame);
		for (int i = 0; i < is.size(); i++)
		{
			res[is[i]] = n[i];
		}
	  }
	  return Arr::createL(res, o->shape);
	}
}
