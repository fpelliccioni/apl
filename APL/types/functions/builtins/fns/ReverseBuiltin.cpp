#include <APL/ReverseBuiltin.h>
#include <APL/Arr.h>
#include <APL/Primitive.h>
#include <APL/errors/RankError.h>
#include <APL/errors/LengthError.h>
#include <APL/arrs/DoubleArr.h>
#include <APL/errors/DomainError.h>
#include <APL/MinusBuiltin.h>
#include <APL/arrs/BitArr.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;

	std::wstring ReverseBuiltin::repr()
	{
	  return L"⌽";
	}

	std::shared_ptr<Value> ReverseBuiltin::call(std::shared_ptr<Value> w, int dim)
	{
	  return (std::static_pointer_cast<Arr>(w))->reverseOn(-dim - 1);
	}

	std::shared_ptr<Value> ReverseBuiltin::call(std::shared_ptr<Value> w)
	{
	  return on(w);
	}

	std::shared_ptr<Value> ReverseBuiltin::on(std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
	  {
		  return w;
	  }
	  return (std::static_pointer_cast<Arr>(w))->reverseOn(w->rank - 1);
	}

	std::shared_ptr<Value> ReverseBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return call(w);
	}

	std::shared_ptr<Value> ReverseBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Primitive>(a) != nullptr)
	  {
		  return on(a->asInt(), w->rank - 1, w);
	  }
	  if (a->rank + 1 != w->rank)
	  {
		  throw RankError(L"(1 + ⍴⍴⍺) ≠ ⍴⍴⍵", shared_from_this());
	  }
	  std::vector<int> as = a->shape;
	  std::vector<int> ws = w->shape;
	  for (int i = 0; i < as.size(); i++)
	  {
		if (as[i] != ws[i])
		{
			throw LengthError(L"expected shape prefixes to match", shared_from_this());
		}
	  }
	  std::vector<int> rots = a->ofShape(std::vector<int>{a->ia})->asIntVec();
	  int block = w->shape[w->rank - 1];
	  int cb = 0;
	  if (w->quickDoubleArr())
	  {
		std::vector<double> vs = w->asDoubleArr();
		std::vector<double> res(w->ia);
		for (int i = 0; i < rots.size(); i++, cb += block)
		{
		  int pA = rots[i];
		  pA = Math::floorMod(pA, block);
		  int pB = block - pA;
		  std::copy_n(vs.begin() + cb, pA, res.begin() + cb + pB);
		  std::copy_n(vs.begin() + cb + pA, pB, res.begin() + cb);
		}
		return std::make_shared<DoubleArr>(res, w->shape);
	  }
	  else
	  {
		std::vector<std::shared_ptr<Value>> vs = w->values();
		std::vector<std::shared_ptr<Value>> res(w->ia);
		for (int i = 0; i < rots.size(); i++, cb += block)
		{
		  int pA = rots[i];
		  pA = Math::floorMod(pA, block);
		  int pB = block - pA;
		  std::copy_n(vs.begin() + cb, pA, res.begin() + cb + pB);
		  std::copy_n(vs.begin() + cb + pA, pB, res.begin() + cb);
		}
		return Arr::create(res, w->shape);
	  }
	}

	std::shared_ptr<Value> ReverseBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DervDimFn> dims)
	{
	  int dim = dims->singleDim(w->rank);
	  if (std::dynamic_pointer_cast<Primitive>(a) != nullptr)
	  {
		  return on(a->asInt(), dim, w);
	  }
	  throw DomainError(L"A⌽[n]B not implemented for non-scalar A", shared_from_this());
	}

	std::shared_ptr<Value> ReverseBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return call(numM(MinusBuiltin::NF, a), w);
	}

	std::shared_ptr<Value> ReverseBuiltin::on(int a, int dim, std::shared_ptr<Value> w)
	{
	  if (w->ia == 0)
	  {
		  return w;
	  }
	  if (a == 0)
	  {
		  return w;
	  }
	  int rowsz = w->shape[dim];
	  a = Math::floorMod(a, rowsz);
	  int block = w->ia; // parts to rotate; each takes 2 arraycopy calls
	  for (int i = 0; i < dim; i++)
	  {
		block /= w->shape[i];
	  }
	  int sub = block / rowsz; // individual rotatable items
	  int pA = sub * a; // first part
	  int pB = block - pA; // second part
	  // System.out.println(block+" "+rowsz+" "+bam+" "+sub+" "+pA+" "+pB);
	  if (std::dynamic_pointer_cast<BitArr>(w) != nullptr && w->rank == 1)
	  {
		std::shared_ptr<BitArr> wb = std::static_pointer_cast<BitArr>(w);
		std::shared_ptr<BitArr::BA> c = std::make_shared<BitArr::BA>(wb->shape);
		c->add(wb, a, wb->ia);
		c->add(wb, 0, a);
		return c->finish();
	  }
	  else if (w->quickDoubleArr())
	  {
		std::vector<double> vs = w->asDoubleArr();
		std::vector<double> res(w->ia);
		for (int cb = 0; cb < w->ia; cb += block)
		{
		  std::copy_n(vs.begin() + cb, pA, res.begin() + cb + pB);
		  std::copy_n(vs.begin() + cb + pA, pB, res.begin() + cb);
		}
		return std::make_shared<DoubleArr>(res, w->shape);
	  }
	  else
	  {
		std::vector<std::shared_ptr<Value>> vs = w->values();
		std::vector<std::shared_ptr<Value>> res(w->ia);
		for (int cb = 0; cb < w->ia; cb += block)
		{
		  std::copy_n(vs.begin() + cb, pA, res.begin() + cb + pB);
		  std::copy_n(vs.begin() + cb + pA, pB, res.begin() + cb);
		}
		return Arr::create(res, w->shape);
	  }
	}
}
