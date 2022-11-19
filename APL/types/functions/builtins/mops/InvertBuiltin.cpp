#include <APL/InvertBuiltin.h>

namespace APL::types::functions::builtins::mops
{
	using NYIError = APL::errors::NYIError;
	using namespace APL::types;
	using namespace APL::types::functions;

	std::shared_ptr<Value> InvertBuiltin::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::shared_ptr<Fun> ff = isFn(f);
	  return ff->callInv(w);
	}

	std::shared_ptr<Value> InvertBuiltin::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::shared_ptr<Fun> ff = isFn(f);
	  return ff->callInvW(a, w);
	}

	std::shared_ptr<Value> InvertBuiltin::callInvW(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Fun> ff = isFn(f);
	  return ff->call(a, w);
	}

	std::shared_ptr<Value> InvertBuiltin::callInvA(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  throw NYIError(L"InvertBuiltin invert ⍺", shared_from_this());
	}

	std::shared_ptr<Fun> InvertBuiltin::invertM(std::shared_ptr<Fun> f)
	{
	  return std::make_shared<FunAnonymousInnerClass>(f);
	}

	InvertBuiltin::FunAnonymousInnerClass::FunAnonymousInnerClass(std::shared_ptr<APL::types::Fun> f)
	{
		this->f = f;
	}

	std::wstring InvertBuiltin::FunAnonymousInnerClass::repr()
	{
		return f->repr() + L"⍣¯1";
	}

	std::shared_ptr<Value> InvertBuiltin::FunAnonymousInnerClass::call(std::shared_ptr<Value> w)
	{
	  return f->callInv(w);
	}

	std::shared_ptr<Fun> InvertBuiltin::invertW(std::shared_ptr<Fun> f)
	{
	  return std::make_shared<FunAnonymousInnerClass2>(f);
	}

	InvertBuiltin::FunAnonymousInnerClass2::FunAnonymousInnerClass2(std::shared_ptr<APL::types::Fun> f)
	{
		this->f = f;
	}

	std::wstring InvertBuiltin::FunAnonymousInnerClass2::repr()
	{
		return f->repr() + L"⍣¯1";
	}

	std::shared_ptr<Value> InvertBuiltin::FunAnonymousInnerClass2::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return f->callInvW(a, w);
	}

	std::shared_ptr<Value> InvertBuiltin::FunAnonymousInnerClass2::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return f->call(a, w);
	}

	std::shared_ptr<Fun> InvertBuiltin::invertA(std::shared_ptr<Fun> f)
	{
	  return std::make_shared<FunAnonymousInnerClass3>(f);
	}

	InvertBuiltin::FunAnonymousInnerClass3::FunAnonymousInnerClass3(std::shared_ptr<APL::types::Fun> f)
	{
		this->f = f;
	}

	std::wstring InvertBuiltin::FunAnonymousInnerClass3::repr()
	{
		return f->repr() + L"⍨⍣¯1⍨";
	}

	std::shared_ptr<Value> InvertBuiltin::FunAnonymousInnerClass3::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return f->callInvA(a, w);
	}

	std::shared_ptr<Value> InvertBuiltin::FunAnonymousInnerClass3::callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return f->call(a, w);
	}

	std::wstring InvertBuiltin::repr()
	{
	  return L"¯";
	}
}
