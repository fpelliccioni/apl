//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/RhoBuiltin.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/Num.h>
#include <APL/errors/LengthError.h>
#include <APL/types/arrs/SingleItemArr.h>
#include <APL/types/arrs/BitArr.h>
#include <APL/types/Primitive.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::fns
{
	using Main = APL::Main;
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using Arrays = java::util::Arrays;

	std::wstring RhoBuiltin::repr()
	{
	  return L"⍴";
	}

	std::shared_ptr<Value> RhoBuiltin::call(std::shared_ptr<Value> w)
	{
	  return Main::toAPL(w->shape);
	}

	std::shared_ptr<Value> RhoBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (a->rank > 1)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍴: multidimensional shape (⍴⍺ is " + Main::formatAPL(a->shape) + L")", shared_from_this(), a));
	  }
	  std::vector<int> sh;
	  int ia;
	  std::optional<int> emptyPos;
	  if (a->quickDoubleArr())
	  {
		sh = a->asIntVec();
		ia = Arr::prod(sh);
	  }
	  else
	  {
		sh = std::vector<int>(a->ia);
		ia = 1;
		for (int i = 0; i < sh.size(); i++)
		{
		  std::shared_ptr<Value> v = a[i];
		  if (std::dynamic_pointer_cast<Num>(v) != nullptr)
		  {
			int c = v->asInt();
			sh[i] = c;
			ia *= c;
		  }
		  else if (v->ia == 0)
		  {
			if (!emptyPos)
			{
				emptyPos = i;
			}
			else
			{
				throw DomainError(L"⍴: shape contained multiple ⍬s", shared_from_this(), v);
			}
		  }
		  else
		  {
			  throw DomainError(StringHelper::wstring_to_string(L"⍴: shape contained " + v->humanType(true), shared_from_this(), v));
		  }
		}
	  }

	  if (emptyPos)
	  {
		if (w->ia % ia != 0)
		{
		  std::shared_ptr<StringBuilder> b = std::make_shared<StringBuilder>();
		  for (auto v : a)
		  {
			  b->append(v)->append(L' ');
		  }
		  b->deleteCharAt(b->length() - 1);
		  throw LengthError(StringHelper::wstring_to_string(L"⍴: empty dimension not perfect (⍺ ≡ " + b + L"; " + std::to_wstring(w->ia) + L" = ≢⍵)", shared_from_this(), w));
		}
		sh[emptyPos] = w->ia / ia;
		return w->ofShape(sh);
	  }
	  else if (ia == w->ia)
	  {
		  return w->ofShape(sh);
	  }

	  if (w->ia == 0)
	  {
		return SingleItemArr::maybe(w->prototype(), sh);

	  }
	  else if (w->scalar())
	  {
		return SingleItemArr::maybe(w->first(), sh);

	  }
	  else if (std::dynamic_pointer_cast<BitArr>(w) != nullptr)
	  {
		if (sh.empty() && !Main::enclosePrimitives)
		{
			return w[0];
		}
		std::shared_ptr<BitArr> wb = std::static_pointer_cast<BitArr>(w);
		std::shared_ptr<BitArr::BA> res = std::make_shared<BitArr::BA>(sh);
		int full = ia / wb->ia;
		int frac = ia % wb->ia;
		for (int i = 0; i < full; i++)
		{
			res->add(wb);
		}
		res->add(wb, 0, frac);
		return res->finish();
	  }
	  else if (w->quickDoubleArr())
	  {
		assert(!(std::dynamic_pointer_cast<Primitive>(w) != nullptr));
		if (sh.empty() && !Main::enclosePrimitives)
		{
			return w[0];
		}
		std::vector<double> inp = w->asDoubleArr();
		std::vector<double> res(ia);
		int p = 0;
		for (int i = 0; i < ia; i++)
		{
		  res[i] = inp[p++];
		  if (p == w->ia)
		  {
			  p = 0;
		  }
		}
		return std::make_shared<DoubleArr>(res, sh);
	  }
	  else if (std::dynamic_pointer_cast<ChrArr>(w) != nullptr)
	  {
		if (sh.empty() && !Main::enclosePrimitives)
		{
			return w[0];
		}
		std::wstring inp = (std::static_pointer_cast<ChrArr>(w))->s;
		std::vector<wchar_t> res(ia);
		int p = 0;
		for (int i = 0; i < ia; i++)
		{
		  res[i] = inp[p++];
		  if (p == w->ia)
		  {
			  p = 0;
		  }
		}
		return std::make_shared<ChrArr>(res, sh);
	  }
	  else
	  {
		if (sh.empty() && std::dynamic_pointer_cast<Primitive>(w->first()) != nullptr && !Main::enclosePrimitives)
		{
			return w[0];
		}
		std::vector<std::shared_ptr<Value>> arr(ia);
		int index = 0;
		for (int i = 0; i < ia; i++)
		{
		  arr[i] = w[index++];
		  if (index == w->ia)
		  {
			  index = 0;
		  }
		}
		return Arr::create(arr, sh);
	  }
	}

	std::shared_ptr<Value> RhoBuiltin::underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(a, w)) : std::static_pointer_cast<Value>(o);
	  for (int i = 0; i < a->ia; i++)
	  {
		std::shared_ptr<Value> c = a[i];
		if (!(std::dynamic_pointer_cast<Num>(c) != nullptr))
		{ // a⍬b ⍴ w - must use all items
		  if (w->rank == 0 && std::dynamic_pointer_cast<Primitive>(v->first()) != nullptr)
		  {
			  return v->first();
		  }
		  if (v->ia != w->ia)
		  {
			  throw DomainError(L"⍢⍴ expected equal amount of output & output items", shared_from_this());
		  }
		  return v->ofShape(w->shape);
		}
	  }
	  std::vector<int> sh = a->asIntVec();
	  int am = Arr::prod(sh);
	  if (am > w->ia)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍢(" + Main::formatAPL(sh) + L"⍴) applied on array with less items than " + std::to_wstring(am), shared_from_this()));
	  }
	  if (!Arrays::equals(sh, v->shape))
	  {
		  throw DomainError(L"⍢⍴ expected equal amount of output & output items", shared_from_this());
	  }
	  std::vector<std::shared_ptr<Value>> vs(w->ia);
	  std::copy_n(v->values().begin(), am, vs.begin());
	  std::copy_n(w->values().begin() + am, vs.size() - am, vs.begin() + am);
	  return Arr::createL(vs, w->shape);
	}
}
