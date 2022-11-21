#include <APL/FlipBuiltin.h>
#include <APL/types/Arr.h>
#include <APL/types/Primitive.h>
#include <APL/ReverseBuiltin.h>
#include <APL/MinusBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	// using namespace APL::types;
	// using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;

	std::string FlipBuiltin::repr()
	{
	  return L"⊖";
	}

	std::shared_ptr<APL::types::Value> FlipBuiltin::call(std::shared_ptr<APL::types::Value> w, int dim)
	{
	  return (std::static_pointer_cast<Arr>(w))->reverseOn(dim);
	}

	std::shared_ptr<APL::types::Value> FlipBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
	  {
		  return w;
	  }
	  return (std::static_pointer_cast<Arr>(w))->reverseOn(0);
	}

	std::shared_ptr<APL::types::Value> FlipBuiltin::callInv(std::shared_ptr<APL::types::Value> w)
	{
	  return call(w);
	}

	std::shared_ptr<APL::types::Value> FlipBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  if (std::dynamic_pointer_cast<Primitive>(a) != nullptr)
	  {
		  return ReverseBuiltin::on(a->asInt(), 0, w);
	  }
	  throw DomainError(L"A⊖B not implemented for non-scalar A", shared_from_this());
	}

	std::shared_ptr<APL::types::Value> FlipBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DervDimFn> dims)
	{
	  int dim = dims->singleDim(w->rank);
	  if (std::dynamic_pointer_cast<Primitive>(a) != nullptr)
	  {
		  return ReverseBuiltin::on(a->asInt(), w->rank - dim - 1, w);
	  }
	  throw DomainError(L"A⊖[n]B not implemented for non-scalar A", shared_from_this());
	}

	std::shared_ptr<APL::types::Value> FlipBuiltin::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return call(numM(MinusBuiltin::NF, a), w);
	}
}
