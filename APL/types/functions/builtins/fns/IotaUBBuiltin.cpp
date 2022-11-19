#include <APL/IotaUBBuiltin.h>
#include <APL/arrs/BitArr.h>
#include <APL/arrs/DoubleArr.h>
#include <APL/Main.h>
#include <APL/Indexer.h>
#include <APL/Num.h>
#include <APL/arrs/HArr.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL;
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using ReduceBuiltin = APL::types::functions::builtins::mops::ReduceBuiltin;
const std::shared_ptr<Fun> IotaUBBuiltin::fn = (std::make_shared<APL::types::functions::builtins::mops::ReduceBuiltin>())->derive(std::make_shared<CeilingBuiltin>());

	std::wstring IotaUBBuiltin::repr()
	{
	  return L"⍸";
	}

	IotaUBBuiltin::IotaUBBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
	{
	}

	std::shared_ptr<Value> IotaUBBuiltin::call(std::shared_ptr<Value> w)
	{
	  int IO = sc->IO;
	  int sum = static_cast<int>(w->sum());
	  if (w->rank == 1)
	  {
		if (sum < 0)
		{
		  for (auto v : w)
		  {
			  if (v->asDouble() < 0)
			  {
				  throw DomainError(StringHelper::wstring_to_string(L"⍸: ⍵ contained " + v, shared_from_this(), w));
			  }
		  }
		}
		auto *sub = std::vector<double>(sum);
		int p = 0;

		if (std::dynamic_pointer_cast<BitArr>(w) != nullptr)
		{
		  std::shared_ptr<BitArr::BR> r = (std::static_pointer_cast<BitArr>(w))->read();
		  for (int i = 0; i < w->ia; i++)
		  {
			if (r->read())
			{
				sub[p++] = i + IO;
			}
		  }
		}
		else
		{
		  std::vector<double> da = w->asDoubleArr();
		  for (int i = 0; i < w->ia; i++)
		  {
			int v = static_cast<int>(da[i]);
			if (v < 0)
			{
				throw DomainError(StringHelper::wstring_to_string(L"⍸: ⍵ contained " + std::to_wstring(v), shared_from_this(), w));
			}
			for (int j = 0; j < v; j++)
			{
			  sub[p++] = i + IO;
			}
		  }
		}
		return std::make_shared<DoubleArr>(sub);
	  }
	  else
	  {
		std::vector<double> wd = w->asDoubleArr();
		if (Main::vind)
		{ // ⎕VI←1
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] res = new double[w.rank][sum];
		  std::vector<std::vector<double>> res = RectangularVectors::RectangularDoubleVector(w->rank, sum);
		  int ri = 0;
		  std::shared_ptr<Indexer> idx = std::make_shared<Indexer>(w->shape, IO);
		  int rank = res.size();
		  for (int i = 0; i < w->ia; i++)
		  {
			std::vector<int> p = idx->next();
			int n = Num::toInt(wd[idx->pos()]);
			if (n > 0)
			{
			  for (int k = 0; k < rank; k++)
			  {
				for (int j = 0; j < n; j++)
				{
					res[k][ri + j] = p[k];
				}
			  }
			  ri += n;
			}
			else if (n != 0)
			{
				throw DomainError(StringHelper::wstring_to_string(L"⍸: ⍵ contained " + std::to_wstring(n), shared_from_this(), w));
			}
		  }
		  std::vector<std::shared_ptr<Value>> resv(rank);
		  for (int i = 0; i < rank; i++)
		  {
			  resv[i] = std::make_shared<DoubleArr>(res[i]);
		  }
		  return std::make_shared<HArr>(resv);
		}
		else
		{ // ⎕VI←0
		  std::vector<std::shared_ptr<Value>> res(sum);
		  int ri = 0;
		  std::shared_ptr<Indexer> idx = std::make_shared<Indexer>(w->shape, IO);
		  for (int i = 0; i < w->ia; i++)
		  {
			std::vector<int> p = idx->next();
			int n = Num::toInt(wd[idx->pos()]);
			if (n > 0)
			{
			  std::shared_ptr<DoubleArr> pos = Main::toAPL(p);
			  for (int j = 0; j < n; j++)
			  {
				  res[ri++] = pos;
			  }
			}
			else if (n != 0)
			{
				throw DomainError(StringHelper::wstring_to_string(L"⍸: ⍵ contained " + std::to_wstring(n), shared_from_this(), w));
			}
		  }
		  return std::make_shared<HArr>(res);
		}
	  }
	}

	std::shared_ptr<Value> IotaUBBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  int IO = sc->IO;
	  std::vector<int> sh = fn->call(w)->asIntVec();
	  int ia = 1;
	  for (int i = 0; i < sh.size(); i++)
	  {
		sh[i] = std::max(0, sh[i] + 1 - IO);
		ia *= sh[i];
	  }
	  std::vector<double> arr(ia);
	  for (auto v : w)
	  {
		std::vector<int> c = v->asIntVec();
		arr[Indexer::fromShape(sh, c, IO)]++;
	  }
	  return std::make_shared<DoubleArr>(arr, sh);
	}
}
