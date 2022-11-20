//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/types/functions/builtins/fns/UpArrowBuiltin.h>
#include <APL/types/Arr.h>
#include <APL/types/arrs/BitArr.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/arrs/EmptyArr.h>
#include <APL/Main.h>
#include <APL/types/Fun.h>
#include <APL/errors/RankError.h>
#include <APL/SimpleIndexer.h>
#include <APL/Indexer.h>
#include <APL/errors/DomainError.h>
#include <APL/CatBuiltin.h>
#include <APL/errors/LengthError.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;

	std::wstring UpArrowBuiltin::repr()
	{
	  return L"↑";
	}

	std::shared_ptr<Value> UpArrowBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Arr>(w) != nullptr)
	  {
		if (std::dynamic_pointer_cast<DoubleArr>(w) != nullptr || std::dynamic_pointer_cast<ChrArr>(w) != nullptr || std::dynamic_pointer_cast<BitArr>(w) != nullptr)
		{
			return w;
		}
		std::vector<std::shared_ptr<Value>> subs = w->values();
		return merge(subs, w->shape, shared_from_this());
	  }
	  else
	  {
		  return w;
	  }
	}

	std::shared_ptr<Value> UpArrowBuiltin::merge(std::vector<std::shared_ptr<Value>> &vals, std::vector<int> &sh, std::shared_ptr<Tokenable> blame)
	{
	  if (vals.empty())
	  {
		  return EmptyArr::SHAPE0N;
	  }

	  std::shared_ptr<Value> first = vals[0];
	  std::vector<int> def(first->rank);
	  std::copy_n(first->shape.begin(), def.size(), def.begin());
	  bool allNums = true;
	  bool eqShapes = true;
	  for (auto v : vals)
	  {
		if (v->rank != def.size())
		{
		  std::wstring msg = blame + L": expected equal ranks of items (shapes " + Main::formatAPL(first->shape) + L" vs " + Main::formatAPL(v->shape) + L")";
		  if (std::dynamic_pointer_cast<Callable>(blame) != nullptr)
		  {
			  throw RankError(msg, std::static_pointer_cast<Callable>(blame), v);
		  }
		  else
		  {
			  throw RankError(msg, v);
		  }
		}
		for (int i = 0; i < def.size(); i++)
		{
		  if (v->shape[i] != def[i])
		  {
			eqShapes = false;
			if (v->shape[i] > def[i])
			{
			  def[i] = v->shape[i];
			}
		  }
		}
		if (!v->quickDoubleArr())
		{
		  allNums = false;
		}
	  }
	  int subIA = Arr::prod(def);
	  int totalIA = subIA * Arr::prod(sh);
	  std::vector<int> resShape(def.size() + sh.size());
	  std::copy_n(sh.begin(), sh.size(), resShape.begin());
	  std::copy_n(def.begin(), def.size(), resShape.begin() + sh.size());

	  if (eqShapes)
	  {
		if (allNums)
		{
		  std::vector<double> res(totalIA);

		  int i = 0;
		  for (auto v : vals)
		  {
			std::vector<double> da = v->asDoubleArr();
			std::copy_n(da.begin(), da.size(), res.begin() + i);
			i += subIA;
		  }
		  return std::make_shared<DoubleArr>(res, resShape);
		}
		std::vector<std::shared_ptr<Value>> res(totalIA);

		int i = 0;
		for (auto v : vals)
		{
		  std::vector<std::shared_ptr<Value>> va = v->values();
		  std::copy_n(va.begin(), va.size(), res.begin() + i);
		  i += subIA;
		}
		return Arr::create(res, resShape);
	  }

	  if (allNums)
	  {
		std::vector<double> res(totalIA);

		int i = 0;
		for (auto v : vals)
		{
		  std::vector<double> c = v->asDoubleArr();
		  int k = 0;
		  for (auto j : std::make_shared<SimpleIndexer>(def, v->shape))
		  {
			res[i + j] = c[k++];
		  }
		  // automatic zero padding
		  i += subIA;
		}

		return std::make_shared<DoubleArr>(res, resShape);
	  }


	  std::vector<std::shared_ptr<Value>> res(totalIA);
	  int i = 0;
	  for (auto v : vals)
	  {
		std::shared_ptr<Value> proto = v->prototype();
		for (auto c : std::make_shared<Indexer>(def, 0))
		{
		  res[i++] = v->at(c, proto);
		}
	  }
	  return Arr::create(res, resShape);
	}

	std::shared_ptr<Value> UpArrowBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::vector<int> gsh = a->asIntVec();
	  if (gsh.empty())
	  {
		  return w;
	  }
	  if (gsh.size() > w->rank)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"↑: ≢⍺ should be less than ⍴⍴⍵ (" + std::to_wstring(gsh.size()) + L" = ≢⍺; " + Main::formatAPL(w->shape) + L" ≡ ⍴⍵)", shared_from_this()));
	  }
	  std::vector<int> sh(w->rank);
	  std::copy_n(gsh.begin(), gsh.size(), sh.begin());
	  std::copy_n(w->shape.begin() + gsh.size(), sh.size() - gsh.size(), sh.begin() + gsh.size());
	  std::vector<int> off(sh.size());
	  for (int i = 0; i < gsh.size(); i++)
	  {
		int d = gsh[i];
		if (d < 0)
		{
		  sh[i] = -d;
		  off[i] = w->shape[i] - sh[i];
		}
		else
		{
			off[i] = 0;
		}
	  }
	  return on(sh, off, w, shared_from_this());
	}

	std::shared_ptr<Value> UpArrowBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DervDimFn> dims)
	{
	  std::vector<int> axV = a->asIntVec();
	  std::vector<int> axK = dims->dims(w->rank);
	  if (axV.size() != axK.size())
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"↑: expected ⍺ and axis specification to have equal number of items (⍺≡" + Main::formatAPL(axV) + L"; axis≡" + dims->format() + L")", shared_from_this(), dims));
	  }
	  std::vector<int> sh = w->shape.clone();
	  std::vector<int> off(sh.size());
	  for (int i = 0; i < axV.size(); i++)
	  {
		int ax = axK[i];
		int am = axV[i];
		sh[ax] = std::abs(am);
		if (am < 0)
		{
			off[ax] = w->shape[ax] + am;
		}
	  }
	  return on(sh, off, w, shared_from_this());
	}

	std::shared_ptr<Value> UpArrowBuiltin::on(std::vector<int> &sh, std::vector<int> &off, std::shared_ptr<Value> w, std::shared_ptr<Callable> blame)
	{
	  int rank = sh.size();
	  assert(rank == off.size() && rank == w->rank);
	  for (int i = 0; i < rank; i++)
	  {
		if (off[i] < 0)
		{
			throw DomainError(blame + L": requesting item before first" + (rank > 1? L" at axis " + std::to_wstring(i) + L"+⎕IO" : L""), blame);
		}
		if (off[i] + sh[i] > w->shape[i])
		{
			throw DomainError(blame + L": requesting item after end" + (rank > 1? L" at axis " + std::to_wstring(i) + L"+⎕IO" : L""), blame);
		}
	  }
	  if (rank == 1)
	  {
		int s = off[0];
		int l = sh[0];
		if (std::dynamic_pointer_cast<BitArr>(w) != nullptr)
		{
		  std::shared_ptr<BitArr> wb = std::static_pointer_cast<BitArr>(w);
		  if (s == 0)
		  {
			std::vector<long long> ls(BitArr::sizeof_Keyword(l));
			std::copy_n(wb->arr.begin(), ls.size(), ls.begin());
			return std::make_shared<BitArr>(ls, std::vector<int>{l});
		  }
		  else
		  {
			std::shared_ptr<BitArr::BA> res = std::make_shared<BitArr::BA>(l);
			res->add(wb, s, w->ia);
			return res->finish();
		  }
		}
		if (std::dynamic_pointer_cast<ChrArr>(w) != nullptr)
		{
		  std::vector<wchar_t> res(l);
		  std::wstring ws = (std::static_pointer_cast<ChrArr>(w))->s;
		  ws.getChars(s, s + l, res, 0); // ≡ for (int i = 0; i < l; i++) res[i] = ws.charAt(s+i);
		  return std::make_shared<ChrArr>(res);
		}
		if (w->quickDoubleArr())
		{
		  std::vector<double> res(l);
		  std::vector<double> wd = w->asDoubleArr();
		  std::copy_n(wd.begin() + s, l, res.begin()); // ≡ for (int i = 0; i < l; i++) res[i] = wd[s+i];
		  return std::make_shared<DoubleArr>(res);
		}

		std::vector<std::shared_ptr<Value>> res(l);
		for (int i = 0; i < l; i++)
		{
			res[i] = w[s + i];
		}
		return Arr::create(res);
	  }
	  int ia = Arr::prod(sh);
	  if (std::dynamic_pointer_cast<ChrArr>(w) != nullptr)
	  {
		std::vector<wchar_t> arr(ia);
		std::wstring s = (std::static_pointer_cast<ChrArr>(w))->s;
		int i = 0;
		for (auto index : std::make_shared<Indexer>(sh, off))
		{
		  arr[i] = s[Indexer::fromShape(w->shape, index, 0)];
		  i++;
		}
		return std::make_shared<ChrArr>(arr, sh);
	  }
	  if (w->quickDoubleArr())
	  {
		std::vector<double> arr(ia);
		std::vector<double> wd = w->asDoubleArr();
		int i = 0;
		for (auto index : std::make_shared<Indexer>(sh, off))
		{
		  arr[i] = wd[Indexer::fromShape(w->shape, index, 0)];
		  i++;
		}
		return std::make_shared<DoubleArr>(arr, sh);
	  }
	  std::vector<std::shared_ptr<Value>> arr(ia);
	  int i = 0;
	  for (auto index : std::make_shared<Indexer>(sh, off))
	  {
		arr[i] = w->at(index, 0);
		i++;
	  }
	  return Arr::create(arr, sh);
	}

	std::shared_ptr<Value> UpArrowBuiltin::underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(a, w)) : std::static_pointer_cast<Value>(o);
	  return undo(a->asIntVec(), v, w, shared_from_this());
	}

	std::shared_ptr<Value> UpArrowBuiltin::undo(std::vector<int> &e, std::shared_ptr<Value> w, std::shared_ptr<Value> origW, std::shared_ptr<Callable> blame)
	{
	  if (e.size() == 1 && w->rank == 1)
	  {
		int am = e[0];
		if (am > 0)
		{
			return CatBuiltin::cat(w, UpArrowBuiltin::on(std::vector<int>{origW->ia - am}, e, origW, blame), 0, blame);
		}
		else
		{
			return CatBuiltin::cat(UpArrowBuiltin::on(std::vector<int>{origW->ia + am}, std::vector<int>{0}, origW, blame), w, 0, blame);
		}
	  }
	  {
		if (w->rank == e.size())
		{
		  for (int i = 0; i < e.size(); i++)
		  {
			if (std::abs(e[i]) != w->shape[i])
			{
				goto failBreak;
			}
		  }
		  goto chkBreak;
		}
		failBreak:
		throw LengthError(StringHelper::wstring_to_string(L"x⍢(N↓): x didn't match expected shape (" + Main::formatAPL(w->shape) + L" ≡ ⍴x; expected " + Main::formatAPL(e) + L")", blame));
	  }
	  chkBreak:
	  std::vector<std::shared_ptr<Value>> r(origW->ia);
	  std::vector<int> s = origW->shape;
	  std::shared_ptr<Indexer> idx = std::make_shared<Indexer>(s, 0);
	  std::vector<int> tmp(e.size());
	  for (auto i : idx)
	  {
		std::shared_ptr<Value> c;
		bool in = true;
		for (int j = 0; j < e.size(); j++)
		{
		  int ep = e[j];
		  int ip = i[j];
		  int lp = s[j];
		  if (ep < 0? ip <= lp + ep - 1 : ip >= ep)
		  {
			in = false;
			break;
		  }
		}
		if (in)
		{
		  for (int j = 0; j < e.size(); j++)
		  {
			tmp[j] = e[j] < 0? i[j] - e[j] - s[j]: i[j];
		  }
		  c = w->simpleAt(tmp);
		}
		else
		{
		  c = origW->simpleAt(i);
		}
		r[idx->pos()] = c;

	  }

	  return Arr::create(r, s);
	}
}
