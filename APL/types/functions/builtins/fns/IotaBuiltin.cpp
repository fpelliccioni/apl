#include <APL/IotaBuiltin.h>
#include <APL/types/Primitive.h>
#include <APL/types/Num.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/BigValue.h>
#include <APL/types/arrs/HArr.h>
#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/Indexer.h>
#include <APL/errors/RankError.h>

namespace APL::types::functions::builtins::fns
{
	// using namespace APL;
	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using HashMap = java::util::HashMap;

	std::string IotaBuiltin::repr()
	{
	  return L"⍳";
	}

	IotaBuiltin::IotaBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
	{
	}

	std::shared_ptr<APL::types::Value> IotaBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  int IO = sc->IO;
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
	  {
		if (std::dynamic_pointer_cast<Num>(w) != nullptr)
		{
		  std::vector<double> res(w->asInt());
		  if (IO == 0)
		  {
			  for (int i = 0; i < res.size(); i++)
			  {
				  res[i] = i;
			  }
		  }
		  else
		  {
			  for (int i = 0; i < res.size(); i++)
			  {
				  res[i] = i + 1;
			  }
		  }
		  return std::make_shared<DoubleArr>(res);
		}
		else if (std::dynamic_pointer_cast<APL::types::BigValue>(w) != nullptr)
		{
		  std::vector<std::shared_ptr<APL::types::Value>> res(w->asInt());
		  for (int i = 0; i < res.size(); i++)
		  {
			res[i] = std::make_shared<APL::types::BigValue>(i + IO);
		  }
		  return std::make_shared<HArr>(res);
		}
	  }
	  if (Main::vind)
	  { // ⎕VI←1
		if (w->rank != 1)
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍳: ⍵ must be a vector (" + Main::formatAPL(w->shape) + L" ≡ ⍴⍵)", shared_from_this(), w));
		}
		int dim = w->ia;
		std::vector<int> shape = w->asIntVec();
		int prod = Arr::prod(shape);
		std::vector<std::shared_ptr<APL::types::Value>> res(dim);
		int blockSize = 1;
		for (int i = dim - 1; i >= 0; i--)
		{
		  std::vector<double> ds(prod);
		  int len = shape[i];
		  int csz = 0;
		  double val = IO;
		  for (int k = 0; k < len; k++)
		  {
			for (int l = 0; l < blockSize; l++)
			{
				ds[csz++] = val;
			}
			val++;
		  }
		  int j = csz;
		  while (j < prod)
		  {
			std::copy_n(ds.begin(), csz, ds.begin() + j);
			j += csz;
		  }
		  res[i] = std::make_shared<DoubleArr>(ds, shape);
		  blockSize *= shape[i];
		}
		return std::make_shared<HArr>(res);
	  }
	  else
	  { // ⎕VI←0
		std::vector<int> shape = w->asIntVec();
		int ia = Arr::prod(shape);
		std::vector<std::shared_ptr<APL::types::Value>> arr(ia);
		int i = 0;
		for (auto c : std::make_shared<Indexer>(shape, IO))
		{
		  arr[i] = Main::toAPL(c);
		  i++;
		}
		return std::make_shared<HArr>(arr, shape);
	  }
	}

	std::shared_ptr<APL::types::Value> IotaBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return on(a, w, sc->IO, shared_from_this());
	}

	std::shared_ptr<APL::types::Value> IotaBuiltin::on(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, int IO, std::shared_ptr<APL::types::Callable> blame)
	{
	  if (w->rank > 1)
	  {
		  throw RankError(L"⍳: ⍵ had rank > 1", blame, w);
	  }
	  if (a->rank > 1)
	  {
		  throw RankError(L"⍳: ⍺ had rank > 1", blame, a);
	  }
	  if (w->ia > 20 && a->ia > 20)
	  {
		std::unordered_map<std::shared_ptr<APL::types::Value>, int> map;
		int ctr = 0;
		for (auto v : a)
		{
		  map.try_emplace(v, ctr);
		  ctr++;
		}
		std::vector<double> res(w->ia);
		ctr = 0;
		double notfound = IO + a->ia;
		for (auto v : w)
		{
		  std::optional<int> f = map[v];
		  res[ctr] = !f? notfound : f.value() + IO;
		  ctr++;
		}
		// w won't be a scalar
		return std::make_shared<DoubleArr>(res, w->shape);
	  }
	  std::vector<double> res(w->ia);
	  int i = 0;
	  for (auto wv : w)
	  {
		int j = 0;
		for (auto av : a)
		{
		  if (av->equals(wv))
		  {
			  break;
		  }
		  j++;
		}
		res[i++] = j + IO;
	  }
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
	  {
		  return std::make_shared<Num>(res[0]);
	  }
	  if (w->rank == 0)
	  {
		  return std::make_shared<Num>(res[0]);
	  }
	  return std::make_shared<DoubleArr>(res, w->shape);
	}
}
