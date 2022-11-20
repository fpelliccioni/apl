#include <APL/TableBuiltin.h>
#include <APL/types/arrs/EmptyArr.h>
#include <APL/types/Fun.h>
#include <APL/types/Num.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/Primitive.h>
#include <APL/types/Arr.h>

namespace APL::types::functions::builtins::mops
{
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::functions;

	std::wstring TableBuiltin::repr()
	{
	  return L"∘.";
	}

	std::shared_ptr<Value> TableBuiltin::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::vector<int> shape(a->rank + w->rank);
	  std::copy_n(a->shape.begin(), a->rank, shape.begin());
	  std::copy_n(w->shape.begin(), w->rank, shape.begin() + a->rank);

	  if (a->ia == 0 || w->ia == 0)
	  {
		  return std::make_shared<EmptyArr>(shape, a->safePrototype());
	  }

	  std::shared_ptr<Fun> ff = std::static_pointer_cast<Fun>(f);


	  int i = 0;
	  std::shared_ptr<Value> first = ff->call(a->first(), w->first());

	  if (std::dynamic_pointer_cast<Num>(first) != nullptr)
	  {
		std::vector<double> dres(a->ia * w->ia);
		bool allNums = true;
		bool firstSkipped = false;
		std::shared_ptr<Value> failure = nullptr;

		for (auto na : a)
		{
		  for (auto nw : w)
		  {
			std::shared_ptr<Value> r;
			if (firstSkipped)
			{
				r = ff->call(na, nw);
			}
			else
			{
			  firstSkipped = true;
			  r = first;
			}
			if (std::dynamic_pointer_cast<Num>(r) != nullptr)
			{
				dres[i++] = (std::static_pointer_cast<Num>(r))->num;
			}
			else
			{
			  allNums = false;
			  failure = r;
			  goto numattBreak;
			}
		  }
			numattContinue:;
		}
		numattBreak:
		if (allNums)
		{
		  if (shape.empty())
		  {
			  return std::make_shared<Num>(dres[0]);
		  }
		  return std::make_shared<DoubleArr>(dres, shape);
		}
		else
		{ // i points to the place the failure should be
		  std::vector<std::shared_ptr<Value>> res(a->ia * w->ia);
		  for (int n = 0; n < i; n++)
		  { // slowly copy the data back..
			res[n] = std::make_shared<Num>(dres[n]);
		  }
		  res[i++] = failure; // insert that horrible thing that broke everything
		  if (i % w->ia != 0)
		  { // finish the damn row..
			std::shared_ptr<Value> va = a[i / w->ia];
			for (int wi = i % w->ia; wi < w->ia; wi++)
			{
			  res[i++] = ff->call(va, w[wi]);
			}
		  }
		  for (int ai = (i + w->ia - 1) / w->ia; ai < a->ia; ai++)
		  { // and do the rest, slowly and horribly
			std::shared_ptr<Value> va = a[ai];
			for (auto vw : w)
			{
			  res[i++] = ff->call(va, vw);
			}
		  }
		  if (shape.empty() && std::dynamic_pointer_cast<Primitive>(res[0]) != nullptr)
		  {
			  return res[0];
		  }
		  return Arr::create(res, shape);
		}
	  }
	  bool firstSkipped = false;
	  std::vector<std::shared_ptr<Value>> arr(a->ia * w->ia);
	  for (auto na : a)
	  {
		for (auto nw : w)
		{
		  if (firstSkipped)
		  {
			  arr[i++] = ff->call(na, nw);
		  }
		  else
		  {
			firstSkipped = true;
			arr[i++] = first;
		  }
		}
	  }
	  if (shape.empty() && std::dynamic_pointer_cast<Primitive>(arr[0]) != nullptr)
	  {
		  return arr[0];
	  }
	  return Arr::create(arr, shape);
	}
}
