#include <APL/TransposeBuiltin.h>
#include <APL/types/Arr.h>

namespace APL::types::functions::builtins::fns
{
	using Indexer = APL::Indexer;
	using namespace APL::types;
	using DoubleArr = APL::types::arrs::DoubleArr;
	using Builtin = APL::types::functions::Builtin;

	std::wstring TransposeBuiltin::repr()
	{
	  return L"⍉";
	}

	std::shared_ptr<Value> TransposeBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (w->scalar())
	  {
		  return w;
	  }
	  if (std::dynamic_pointer_cast<DoubleArr>(w) != nullptr)
	  {
		std::vector<double> dw = w->asDoubleArr();
		std::vector<double> res(w->ia);
		std::vector<int> sh(w->rank);
		for (int i = 0; i < w->rank; i++)
		{
		  sh[i] = w->shape[w->rank - i - 1];
		}
		if (w->rank == 2)
		{
		  int ww = w->shape[0];
		  int wh = w->shape[1];
		  int ip = 0;
		  for (int x = 0; x < ww; x++)
		  {
			int op = x;
			for (int y = 0; y < wh; y++)
			{
			  res[op] = dw[ip++];
			  op += ww;
			}
		  }
		}
		else
		{
		  int ci = 0;
		  for (auto c : std::make_shared<Indexer>(w->shape, 0))
		  {
			std::vector<int> nc(w->rank);
			for (int i = 0; i < w->rank; i++)
			{
			  nc[i] = c[w->rank - i - 1];
			}
			res[Indexer::fromShape(sh, nc, 0)] = dw[ci++];
		  }
		}
		return std::make_shared<DoubleArr>(res, sh);
	  }
	  std::vector<std::shared_ptr<Value>> arr(w->ia);
	  std::vector<int> ns(w->rank);
	  for (int i = 0; i < w->rank; i++)
	  {
		ns[i] = w->shape[w->rank - i - 1];
	  }
	  for (auto c : std::make_shared<Indexer>(w->shape, 0))
	  {
		std::vector<int> nc(w->rank);
		for (int i = 0; i < w->rank; i++)
		{
		  nc[i] = c[w->rank - i - 1];
		}
		arr[Indexer::fromShape(ns, nc, 0)] = w->simpleAt(c);
	  }
	  return Arr::create(arr, ns);
	}

	std::shared_ptr<Value> TransposeBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return call(w);
	}
}
