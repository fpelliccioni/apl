#include <APL/types/functions/DerivedMop.h>

namespace APL::types::functions
{
	using namespace APL::types;
	using TableBuiltin = APL::types::functions::builtins::mops::TableBuiltin;

	DerivedMop::DerivedMop(std::shared_ptr<Obj> aa, std::shared_ptr<Mop> op) : aa(aa), op(op)
	{
	  token = op->token;
	}

	std::shared_ptr<Value> DerivedMop::call(std::shared_ptr<Value> w)
	{
	  return op->call(aa, w, shared_from_this());
	}

	std::shared_ptr<Value> DerivedMop::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return op->call(aa, a, w, shared_from_this());
	}

	std::shared_ptr<Obj> DerivedMop::callObj(std::shared_ptr<Value> w)
	{
	  return op->callObj(aa, w, shared_from_this());
	}

	std::shared_ptr<Obj> DerivedMop::callObj(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return op->callObj(aa, a, w, shared_from_this());
	}

	std::shared_ptr<Value> DerivedMop::callInv(std::shared_ptr<Value> w)
	{
	  return op->callInv(aa, w);
	}

	std::shared_ptr<Value> DerivedMop::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return op->callInvW(aa, a, w);
	}

	std::shared_ptr<Value> DerivedMop::callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return op->callInvA(aa, a, w);
	}

	std::wstring DerivedMop::repr()
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  return std::dynamic_pointer_cast<TableBuiltin>(op) != nullptr? L"∘." + aa->toString() : aa->toString() + op->repr();
	}

	std::shared_ptr<Value> DerivedMop::under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w)
	{
	  return op->under(aa, o, w, shared_from_this());
	}

	std::shared_ptr<Value> DerivedMop::underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return op->underW(aa, o, a, w, shared_from_this());
	}

	std::shared_ptr<Value> DerivedMop::underA(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return op->underA(aa, o, a, w, shared_from_this());
	}
}
