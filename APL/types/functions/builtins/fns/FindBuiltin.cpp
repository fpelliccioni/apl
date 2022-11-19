#include <APL/FindBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using Indexer = APL::Indexer;
	using RankError = APL::errors::RankError;
	using Value = APL::types::Value;
	using BitArr = APL::types::arrs::BitArr;
	using Builtin = APL::types::functions::Builtin;

	std::wstring FindBuiltin::repr()
	{
	  return L"⍷";
	}

	std::shared_ptr<Value> FindBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (a->rank != w->rank)
	  {
		  throw RankError(StringHelper::wstring_to_string(L"⍷: argument ranks should be equal (" + std::to_wstring(a->rank) + L" ≠ " + std::to_wstring(w->rank) + L")", shared_from_this(), w));
	  }
	  std::shared_ptr<BitArr::BC> bc = std::make_shared<BitArr::BC>(w->shape);
	  if (a->rank == 1)
	  {
		if (std::dynamic_pointer_cast<BitArr>(a) != nullptr && std::dynamic_pointer_cast<BitArr>(w) != nullptr)
		{
		  std::vector<long long> ab = (std::static_pointer_cast<BitArr>(a))->arr;
		  std::vector<long long> wb = (std::static_pointer_cast<BitArr>(w))->arr;
		  for (int ir = 0; ir < w->ia - a->ia + 1; ir++)
		  {
			for (int ia = 0; ia < a->ia; ia++)
			{
			  int iw = ia + ir;
			  long long la = ab[ia >> 6] >> (ia & 63);
			  long long lw = wb[iw >> 6] >> (iw & 63);
			  if ((la & 1) != (lw & 1))
			  {
				  goto wContinue;
			  }
			}
			bc->set(ir);
			  wContinue:;
		  }
		  wBreak:;
		}
		else if (a->quickDoubleArr() && w->quickDoubleArr())
		{
		  std::vector<double> ad = a->asDoubleArr();
		  std::vector<double> wd = w->asDoubleArr();
		  for (int ir = 0; ir < w->ia - a->ia + 1; ir++)
		  {
			for (int ia = 0; ia < a->ia; ia++)
			{
			  if (ad[ia] != wd[ia + ir])
			  {
				  goto wContinue;
			  }
			}
			bc->set(ir);
			  wContinue:;
		  }
		  wBreak:;
		}
		else
		{
		  for (int ir = 0; ir < w->ia - a->ia + 1; ir++)
		  {
			for (int ia = 0; ia < a->ia; ia++)
			{
			  if (!a[ia].equals(w[ia + ir]))
			  {
				  goto wContinue;
			  }
			}
			bc->set(ir);
			  wContinue:;
		  }
		  wBreak:;
		}
	  }
	  else
	  {
		std::shared_ptr<Indexer> ind = std::make_shared<Indexer>(Indexer::add(Indexer::sub(w->shape, a->shape), 1), 0);
		for (auto inW : ind)
		{
		  for (auto inA : std::make_shared<Indexer>(a->shape, 0))
		  {
			std::shared_ptr<Value> vA = a->simpleAt(inA);
			std::shared_ptr<Value> vW = w->simpleAt(Indexer::add(inA, inW));
			if (!vA->equals(vW))
			{
				goto wContinue;
			}
		  }
		  bc->set(Indexer::fromShape(w->shape, inW, 0));
			wContinue:;
		}
		wBreak:;
	  }
	  return bc->finish();
	}
}
