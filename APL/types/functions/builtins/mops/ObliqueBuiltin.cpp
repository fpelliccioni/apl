#include <APL/ObliqueBuiltin.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Fun.h>
#include <APL/types/arrs/EmptyArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/errors/RankError.h>
#include <APL/types/arrs/HArr.h>

namespace APL::types::functions::builtins::mops
{
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::functions;
	using UpArrowBuiltin = APL::types::functions::builtins::fns::UpArrowBuiltin;

	std::wstring ObliqueBuiltin::repr()
	{
	  return L"⍁";
	}

	std::shared_ptr<Value> ObliqueBuiltin::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  if (w->rank != 2)
	  {
		  throw DomainError(L"⍁: ⍵ must be a rank 2 array", shared_from_this(), w);
	  }
	  std::shared_ptr<Fun> ff = isFn(f);
	  std::vector<int> sz = w->shape;
	  int H = sz[0];
	  int W = sz[1];
	  int szM = std::max(H, W);
	  int szm = std::min(H, W);
	  int ram = H + W - 1;
	  if (ram <= 0)
	  {
		  return std::make_shared<EmptyArr>(EmptyArr::SHAPE0, w->safePrototype());
	  }

	  std::vector<std::shared_ptr<Value>> res(ram);

	  if (w->quickDoubleArr())
	  {
		std::vector<double> vals = w->asDoubleArr();
		std::vector<std::vector<double>> rows(ram);
		for (int i = 0; i < ram; i++)
		{
		  rows[i] = std::vector<double>(i < szm? i + 1 : i >= szM? szm + szM - i - 1 : szm);
		}
		int p = 0;
		for (int y = 0; y < H; y++)
		{
		  for (int x = 0; x < W; x++)
		  {
			double v = vals[p++];
			int ri = x + y;
			int s = ri > W - 2? y + W - ri - 1 : y;
			rows[ri][s] = v;
		  }
		}
		res[0] = ff->call(std::make_shared<DoubleArr>(rows[0]));
		int rrank = res[0]->rank; // required rank
		for (int i = 0; i < ram; i++)
		{
		  std::shared_ptr<Value> v = ff->call(std::make_shared<DoubleArr>(rows[i]));
		  if (v->rank != rrank)
		  {
			  throw RankError(L"⍁: ⍶ must return equal rank arrays", shared_from_this(), f);
		  }
		  res[i] = v;
		}
	  }
	  else
	  {
		std::vector<std::shared_ptr<Value>> vals = w->values();
		std::vector<std::vector<std::shared_ptr<Value>>> rows(ram);
		for (int i = 0; i < ram; i++)
		{
		  rows[i] = std::vector<std::shared_ptr<Value>>(i < szm? i + 1 : i >= szM? szm + szM - i - 1 : szm);
		}
		int p = 0;
		for (int y = 0; y < H; y++)
		{
		  for (int x = 0; x < W; x++)
		  {
			std::shared_ptr<Value> v = vals[p++];
			int ri = x + y;
			int s = ri > W - 2? y + W - ri - 1 : y;
			rows[ri][s] = v;
		  }
		}
		res[0] = ff->call(std::make_shared<HArr>(rows[0]));
		int rrank = res[0]->rank; // required rank
		for (int i = 0; i < ram; i++)
		{
		  std::shared_ptr<Value> v = ff->call(std::make_shared<HArr>(rows[i]));
		  if (v->rank != rrank)
		  {
			  throw DomainError(L"⍁: ⍶ must return equal rank arrays", shared_from_this(), f);
		  }
		  res[i] = v;
		}
	  }

	  return UpArrowBuiltin::merge(res, std::vector<int>{res.size()}, shared_from_this());
	}
}
