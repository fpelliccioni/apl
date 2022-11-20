#include <APL/Dmop.h>
#include <APL/Main.h>
#include <APL/types/Variable.h>
#include <APL/types/functions/VarArr.h>
#include <APL/types/Settable.h>

namespace APL::types::functions::userDefined
{
	using namespace APL;
	using DomainError = APL::errors::DomainError;
	using DfnTok = APL::tokenizer::types::DfnTok;
	using namespace APL::types;
	using namespace APL::types::functions;

	std::wstring Dmop::repr()
	{
	  return code->toRepr();
	}

	Dmop::Dmop(std::shared_ptr<DfnTok> t, std::shared_ptr<Scope> sc) : Mop(sc), code(t)
	{
	}

	std::shared_ptr<Value> Dmop::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::shared_ptr<Obj> o = callObj(f, w, derv);
	  if (std::dynamic_pointer_cast<Value>(o) != nullptr)
	  {
		  return std::static_pointer_cast<Value>(o);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Was expected to give array, got " + o->humanType(true), shared_from_this()));
	}

	std::shared_ptr<Obj> Dmop::callObj(std::shared_ptr<Obj> aa, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  Main::printdbg(sc, std::vector<std::any> {L"dmop call", w});
	  std::shared_ptr<Scope> nsc = std::make_shared<Scope>(sc);
	  nsc->set(L"⍶", aa);
	  nsc->set(L"⍺", std::make_shared<Variable>(nsc, L"⍺"));
	  nsc->set(L"⍵", w);
	  nsc->set(L"∇", derv);
	  auto res = Main::execLines(code, nsc);
	  if (std::dynamic_pointer_cast<VarArr>(res) != nullptr)
	  {
		  return (std::static_pointer_cast<VarArr>(res))->get();
	  }
	  if (std::dynamic_pointer_cast<Settable>(res) != nullptr)
	  {
		  return (std::static_pointer_cast<Settable>(res))->get();
	  }
	  return res;
	}

	std::shared_ptr<Value> Dmop::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  std::shared_ptr<Obj> o = callObj(f, a, w, derv);
	  if (std::dynamic_pointer_cast<Value>(o) != nullptr)
	  {
		  return std::static_pointer_cast<Value>(o);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Was expected to give array, got " + o->humanType(true), shared_from_this()));
	}

	std::shared_ptr<Obj> Dmop::callObj(std::shared_ptr<Obj> aa, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  Main::printdbg(sc, std::vector<std::any> {L"dmop call", a, w});
	  std::shared_ptr<Scope> nsc = std::make_shared<Scope>(sc);
	  nsc->set(L"⍶", aa);
	  nsc->set(L"⍺", a);
	  nsc->set(L"⍵", w);
	  nsc->set(L"∇", derv);
	  nsc->alphaDefined = true;
	  auto res = Main::execLines(code, nsc);
	  if (std::dynamic_pointer_cast<VarArr>(res) != nullptr)
	  {
		  return (std::static_pointer_cast<VarArr>(res))->get();
	  }
	  if (std::dynamic_pointer_cast<Settable>(res) != nullptr)
	  {
		  return (std::static_pointer_cast<Settable>(res))->get();
	  }
	  return res;
	}
}
