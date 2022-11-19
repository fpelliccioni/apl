//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/CatBuiltin.h>
#include <APL/Primitive.h>
#include <APL/Num.h>
#include <APL/arrs/DoubleArr.h>
#include <APL/Char.h>
#include <APL/arrs/ChrArr.h>
#include <APL/arrs/Shape1Arr.h>
#include <APL/errors/DomainError.h>
#include <APL/errors/RankError.h>
#include <APL/errors/LengthError.h>
#include <APL/arrs/BitArr.h>
#include <APL/Arr.h>
#include <APL/Fun.h>
#include <APL/errors/NYIError.h>
#include <APL/UpArrowBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using Main = APL::Main;
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;
	using Arrays = java::util::Arrays;

	std::wstring CatBuiltin::repr()
	{
	  return L",";
	}

	std::shared_ptr<Value> CatBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
	  {
		if (std::dynamic_pointer_cast<Num>(w) != nullptr)
		{
			return std::make_shared<DoubleArr>(std::vector<double>{(std::static_pointer_cast<Num>(w))->num});
		}
		if (std::dynamic_pointer_cast<Char>(w) != nullptr)
		{
			return std::make_shared<ChrArr>(StringHelper::toString((std::static_pointer_cast<Char>(w))->chr));
		}
		return std::make_shared<Shape1Arr>(w);
	  }
	  return w->ofShape(std::vector<int>{w->ia});
	}

	std::shared_ptr<Value> CatBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  int dim = std::max(a->rank, w->rank) - 1;
	  return cat(a, w, dim, shared_from_this());
	}

	std::shared_ptr<Value> CatBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DervDimFn> dims)
	{
	  int dim = dims->singleDim();
	  if (dim < 0 || dim >= std::max(a->rank, w->rank))
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"dimension " + std::to_wstring(dim) + L" is out of range", shared_from_this()));
	  }
	  return cat(a, w, dim, shared_from_this());
	}

	std::shared_ptr<Value> CatBuiltin::cat(std::shared_ptr<Value> a, std::shared_ptr<Value> w, int k, std::shared_ptr<Callable> blame)
	{
	  bool aScalar = a->rank == 0, wScalar = w->rank == 0;
	  if (aScalar && wScalar)
	  {
		  return cat(std::make_shared<Shape1Arr>(a->first()), w, 0, blame);
	  }

	  std::vector<int> rs = aScalar? w->shape.clone() : a->shape.clone(); // shape of the result
	  if (!aScalar && !wScalar)
	  {
		if (a->rank != w->rank)
		{
			throw RankError(L"ranks not matchable", blame, w);
		}
		for (int i = 0; i < a->rank; i++)
		{
		  if (i != k && a->shape[i] != w->shape[i])
		  {
			  throw LengthError(StringHelper::wstring_to_string(L"lengths not matchable (" + DoubleArr(a->shape) + L" vs " + DoubleArr(w->shape) + L")", blame, w));
		  }
		}
	  }
	  rs[k] += aScalar || wScalar ? 1 : w->shape[k];
	  if (k <= 0 && a->rank == w->rank)
	  {
		if ((std::dynamic_pointer_cast<BitArr>(a) != nullptr || Main::isBool(a)) && (std::dynamic_pointer_cast<BitArr>(w) != nullptr || Main::isBool(w)))
		{
		  bool ab = std::dynamic_pointer_cast<BitArr>(a) != nullptr;
		  bool wb = std::dynamic_pointer_cast<BitArr>(w) != nullptr;

		  std::shared_ptr<BitArr::BA> res = std::make_shared<BitArr::BA>(rs);
		  if (ab)
		  {
			  res->add(std::static_pointer_cast<BitArr>(a));
		  }
		  else
		  {
			  res->add(Main::bool_Keyword(a));
		  }
		  if (wb)
		  {
			  res->add(std::static_pointer_cast<BitArr>(w));
		  }
		  else
		  {
			  res->add(Main::bool_Keyword(w));
		  }

		  return res->finish();
		}
		if (std::dynamic_pointer_cast<DoubleArr>(a) != nullptr && std::dynamic_pointer_cast<DoubleArr>(w) != nullptr)
		{
		  std::vector<double> r(a->ia + w->ia);
		  std::copy_n(a->asDoubleArr().begin(), a->ia, r.begin());
		  std::copy_n(w->asDoubleArr().begin(), w->ia, r.begin() + a->ia);
		  return std::make_shared<DoubleArr>(r, rs);
		}
		std::vector<std::shared_ptr<Value>> r(a->ia + w->ia);
		std::copy_n(a->values().begin(), a->ia, r.begin());
		std::copy_n(w->values().begin(), w->ia, r.begin() + a->ia);
		return Arr::create(r,rs);
	  }
	  int n0 = 1;
	  for (int i = 0; i < k; i++)
	  {
		  n0 *= rs[i]; // product of major dimensions
	  }
	  int n1 = rs[k]; // dimension to catenate on
	  int n2 = 1;
	  for (int i = k + 1; i < rs.size(); i++)
	  {
		  n2 *= rs[i]; // product of minor dimensions
	  }
	  int ad = aScalar ? n2 : a->shape[k] * n2; // chunk size for ⍺
	  int wd = wScalar ? n2 : w->shape[k] * n2; // chunk size for ⍵

	  if (a->quickDoubleArr() && w->quickDoubleArr())
	  {
		std::vector<double> rv(n0 * n1 * n2); // result values
		copyChunksD(aScalar, a->asDoubleArr(), rv, 0, ad, ad + wd);
		copyChunksD(wScalar, w->asDoubleArr(), rv, ad, wd, ad + wd);
		return std::make_shared<DoubleArr>(rv, rs);
	  }
	  else
	  {
		std::vector<std::shared_ptr<Value>> rv(n0 * n1 * n2); // result values
		copyChunks(aScalar, a->values(), rv, 0, ad, ad + wd);
		copyChunks(wScalar, w->values(), rv, ad, wd, ad + wd);
		return Arr::create(rv, rs);
	  }
	}

	void CatBuiltin::copyChunks(bool scalar, std::vector<std::shared_ptr<Value>> &av, std::vector<std::shared_ptr<Value>> &rv, int offset, int ad, int rd)
	{
	  if (scalar)
	  {
		for (int i = offset; i < rv.size(); i += rd)
		{
		  Arrays::fill(rv, i, i + ad, av[0]);
		}
	  }
	  else
	  {
		for (int i = offset, j = 0; i < rv.size(); i += rd, j += ad)
		{ // i:position in rv, j:position in av
		  std::copy_n(av.begin() + j, ad, rv.begin() + i);
		}
	  }
	}

	void CatBuiltin::copyChunksD(bool scalar, std::vector<double> &av, std::vector<double> &rv, int offset, int ad, int rd)
	{
	  if (scalar)
	  {
		for (int i = offset; i < rv.size(); i += rd)
		{
		  Arrays::fill(rv, i, i + ad, av[0]);
		}
	  }
	  else
	  {
		for (int i = offset, j = 0; i < rv.size(); i += rd, j += ad)
		{ // i:position in rv, j:position in av
		  std::copy_n(av.begin() + j, ad, rv.begin() + i);
		}
	  }
	}

	std::shared_ptr<Value> CatBuiltin::under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(w)) : std::static_pointer_cast<Value>(o);
	  if (v->ia != w->ia)
	  {
		  throw DomainError(L"⍢, expected equal amount of output & output items", shared_from_this());
	  }
	  return v->ofShape(w->shape);
	}

	std::shared_ptr<Value> CatBuiltin::underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(a, w)) : std::static_pointer_cast<Value>(o);
	  if (a->rank > 1)
	  {
		  throw NYIError(StringHelper::wstring_to_string(L", inverted on rank " + std::to_wstring(a->rank) + L" ⍺", shared_from_this()));
	  }
	  if (v->rank > 1)
	  {
		  throw NYIError(StringHelper::wstring_to_string(L", inverted on rank " + std::to_wstring(v->rank) + L" ⍵", shared_from_this()));
	  }
	  for (int i = 0; i < a->ia; i++)
	  {
		if (a[i] != v[i])
		{
			throw DomainError(L"inverting , received non-equal prefixes", shared_from_this());
		}
	  }
	  if (w->rank == 0)
	  {
		if (a->ia + 1 != v->ia)
		{
			throw DomainError(L"original ⍵ was of rank ⍬, which is not satisfiable", shared_from_this());
		}
		return v[v->ia - 1];
	  }
	  return UpArrowBuiltin::on(std::vector<int>{v->ia - a->ia}, std::vector<int>{a->ia}, v, shared_from_this());
	}
}
