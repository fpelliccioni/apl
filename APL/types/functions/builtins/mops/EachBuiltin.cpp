//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/EachBuiltin.h>
#include <APL/types/arrs/Rank0Arr.h>
#include <APL/types/Arr.h>
#include <APL/types/arrs/SingleItemArr.h>
#include <APL/errors/LengthError.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Primitive.h>

namespace APL::types::functions::builtins::mops
{
	using Main = APL::Main;
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::functions;
	using LShoeBuiltin = APL::types::functions::builtins::fns::LShoeBuiltin;
	using Arrays = java::util::Arrays;

	std::wstring EachBuiltin::repr()
	{
	  return L"¨";
	}

	std::shared_ptr<Value> EachBuiltin::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  if (w->scalar())
	  {
		  return LShoeBuiltin::on(std::dynamic_pointer_cast<Fun>(f) != nullptr? (std::static_pointer_cast<Fun>(f))->call(w->first()) : std::static_pointer_cast<Value>(f));
	  }
	  if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
	  {
		std::vector<std::shared_ptr<Value>> n(w->ia);
		for (int i = 0; i < n.size(); i++)
		{
		  n[i] = (std::static_pointer_cast<Fun>(f))->call(w[i]);
		}
		return Arr::create(n, w->shape);
	  }
	  else
	  {
		return std::make_shared<SingleItemArr>(std::static_pointer_cast<Value>(f), w->shape);
	  }
	}

	std::shared_ptr<Value> EachBuiltin::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::shared_ptr<Fun> ff = std::static_pointer_cast<Fun>(f);
	  if (w->scalar())
	  {
		std::shared_ptr<Value> w0 = w->first();
		if (a->scalar())
		{
			return LShoeBuiltin::on(ff->call(a->first(), w0));
		}
		std::vector<std::shared_ptr<Value>> n(a->ia);
		for (int i = 0; i < n.size(); i++)
		{
			n[i] = ff->call(a[i], w0);
		}
		return Arr::create(n, a->shape);
	  }
	  if (a->scalar())
	  {
		std::vector<std::shared_ptr<Value>> n(w->ia);
		std::shared_ptr<Value> a0 = a->first();
		for (int i = 0; i < n.size(); i++)
		{
			n[i] = ff->call(a0, w[i]);
		}
		return Arr::create(n, w->shape);
	  }
	  if (!Arrays::equals(a->shape, w->shape))
	  {
		  throw LengthError(StringHelper::wstring_to_string(L"shapes not equal (" + Main::formatAPL(a->shape) + L" vs " + Main::formatAPL(w->shape) + L")", derv, w));
	  }
	  std::vector<std::shared_ptr<Value>> n(w->ia);
	  for (int i = 0; i < n.size(); i++)
	  {
		n[i] = ff->call(a[i], w[i]);
	  }
	  return Arr::create(n, w->shape);
	}

	std::shared_ptr<Value> EachBuiltin::callInv(std::shared_ptr<Obj> f, std::shared_ptr<Value> w)
	{
	  if (!(std::dynamic_pointer_cast<Fun>(f) != nullptr))
	  {
		  throw DomainError(L"can't invert A¨", shared_from_this());
	  }
	  std::vector<std::shared_ptr<Value>> n(w->ia);
	  for (int i = 0; i < n.size(); i++)
	  {
		n[i] = (std::static_pointer_cast<Fun>(f))->callInv(w[i]);
	  }
	  if (w->rank == 0 && std::dynamic_pointer_cast<Primitive>(n[0]) != nullptr)
	  {
		  return n[0];
	  }
	  return Arr::create(n, w->shape);
	}

	std::shared_ptr<Value> EachBuiltin::under(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa);
	  std::vector<std::shared_ptr<Value>> res2(w->ia);
	  rec(aaf, o, w, 0, std::vector<std::shared_ptr<Value>>(w->ia), std::vector<std::shared_ptr<Value>>(1), res2);
	  return Arr::create(res2, w->shape);
	}

	void EachBuiltin::rec(std::shared_ptr<Fun> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> w, int i, std::vector<std::shared_ptr<Value>> &args, std::vector<std::shared_ptr<Value>> &resPre, std::vector<std::shared_ptr<Value>> &res)
	{
	  if (i == args.size())
	  {
		std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(Arr::create(args, w->shape)) : std::static_pointer_cast<Value>(o);
		resPre[0] = v;
	  }
	  else
	  {
		res[i] = aa->under(std::make_shared<FunAnonymousInnerClass>(aa, o, w, i, args, resPre, res)
	   , w[i]);
	  }
	}

	EachBuiltin::FunAnonymousInnerClass::FunAnonymousInnerClass(std::shared_ptr<APL::types::Fun> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w, int i, std::vector<std::shared_ptr<APL::types::Value>> &args, std::vector<std::shared_ptr<APL::types::Value>> &resPre, std::vector<std::shared_ptr<APL::types::Value>> &res)
	{
		this->aa = aa;
		this->o = o;
		this->w = w;
		this->i = i;
		this->args = args;
		this->resPre = resPre;
		this->res = res;
	}

	std::wstring EachBuiltin::FunAnonymousInnerClass::repr()
	{
		return aa->repr() + L"¨";
	}

	std::shared_ptr<Value> EachBuiltin::FunAnonymousInnerClass::call(std::shared_ptr<Value> w1)
	{
		args[i] = w1;
		rec(aa, o, w, i + 1, args, resPre, res);
		return resPre[0][i];
	}

	std::shared_ptr<Value> EachBuiltin::underW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  return underW(isFn(aa), o, a, w, shared_from_this());
	}

	std::shared_ptr<Value> EachBuiltin::underW(std::shared_ptr<Fun> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<Callable> blame)
	{
	  if (a->rank != 0 && w->rank != 0 && !Arrays::equals(a->shape, w->shape))
	  {
		  throw LengthError(StringHelper::wstring_to_string(L"shapes not equal (" + Main::formatAPL(a->shape) + L" vs " + Main::formatAPL(w->shape) + L")", blame, w));
	  }
	  int ia = std::max(a->ia, w->ia);
	  std::vector<std::shared_ptr<Value>> res2(ia);
	  if (a->rank == 0 && !(std::dynamic_pointer_cast<Primitive>(a) != nullptr))
	  {
		  a = std::make_shared<Rank0Arr>(a->first()); // abuse that get doesn't check indexes for simple scalar extension
	  }
	  if (w->rank == 0 && !(std::dynamic_pointer_cast<Primitive>(w) != nullptr))
	  {
		  w = std::make_shared<Rank0Arr>(a->first());
	  }
	  rec(aa, o, a, w, 0, std::vector<std::shared_ptr<Value>>(ia), std::vector<std::shared_ptr<Value>>(1), res2);
	  return Arr::create(res2, w->shape);
	}

	void EachBuiltin::rec(std::shared_ptr<Fun> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, int i, std::vector<std::shared_ptr<Value>> &args, std::vector<std::shared_ptr<Value>> &resPre, std::vector<std::shared_ptr<Value>> &res)
	{
	  if (i == args.size())
	  {
		std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(Arr::create(args, w->shape)) : std::static_pointer_cast<Value>(o);
		resPre[0] = v;
	  }
	  else
	  {
		res[i] = aa->underW(std::make_shared<FunAnonymousInnerClass2>(aa, o, a, w, i, args, resPre, res)
	   , a[i], w[i]);
	  }
	}

	EachBuiltin::FunAnonymousInnerClass2::FunAnonymousInnerClass2(std::shared_ptr<APL::types::Fun> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, int i, std::vector<std::shared_ptr<APL::types::Value>> &args, std::vector<std::shared_ptr<APL::types::Value>> &resPre, std::vector<std::shared_ptr<APL::types::Value>> &res)
	{
		this->aa = aa;
		this->o = o;
		this->a = a;
		this->w = w;
		this->i = i;
		this->args = args;
		this->resPre = resPre;
		this->res = res;
	}

	std::wstring EachBuiltin::FunAnonymousInnerClass2::repr()
	{
		return aa->repr() + L"¨";
	}

	std::shared_ptr<Value> EachBuiltin::FunAnonymousInnerClass2::call(std::shared_ptr<Value> w1)
	{
		args[i] = w1;
		rec(aa, o, a, w, i + 1, args, resPre, res);
		return resPre[0][i];
	}
}