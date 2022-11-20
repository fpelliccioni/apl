#include <APL/types/Obj.h>
#include <APL/types/Arr.h>
#include <APL/types/Char.h>
#include <APL/types/Num.h>
#include <APL/types/APLMap.h>
#include <APL/types/Fun.h>
#include <APL/Null.h>
#include <APL/types/dimensions/Brackets.h>
#include <APL/functions/VarArr.h>
#include <APL/types/Variable.h>
#include <APL/types/dimensions/Pick.h>
#include <APL/types/functions/Mop.h>
#include <APL/types/functions/Dop.h>
#include <APL/functions/ArrFun.h>
#include <APL/types/BigValue.h>

namespace APL::types
{
	using namespace APL;
	using NYIError = APL::errors::NYIError;
	using Token = APL::tokenizer::Token;
	using namespace APL::types::dimensions;
	using namespace APL::types::functions;

	bool Obj::isObj()
	{
	  return type() == Type::array || type() == Type::var;
	}

	bool Obj::equals(std::shared_ptr<Obj> o)
	{
	  return false;
	}

	std::wstring Obj::humanType(bool article)
	{

	  if (std::dynamic_pointer_cast<Arr>(shared_from_this()) != nullptr)
	  {
		  return article? L"an array" : L"array";
	  }
	  if (std::dynamic_pointer_cast<Char>(shared_from_this()) != nullptr)
	  {
		  return article? L"a character" : L"character";
	  }
	  if (std::dynamic_pointer_cast<Num>(shared_from_this()) != nullptr)
	  {
		  return article? L"a number" : L"number";
	  }
	  if (std::dynamic_pointer_cast<APLMap>(shared_from_this()) != nullptr)
	  {
		  return article? L"a map" : L"map";
	  }
	  if (std::dynamic_pointer_cast<Fun>(shared_from_this()) != nullptr)
	  {
		  return article? L"a function" : L"function";
	  }
	  if (std::dynamic_pointer_cast<Null>(shared_from_this()) != nullptr)
	  {
		  return article? L"javanull" : L"javanull";
	  }
	  if (std::dynamic_pointer_cast<Brackets>(shared_from_this()) != nullptr)
	  {
		  return article? L"brackets" : L"brackets";
	  }
	  if (std::dynamic_pointer_cast<VarArr>(shared_from_this()) != nullptr)
	  {
		  return article? L"a vararr" : L"vararr";
	  }
	  if (std::dynamic_pointer_cast<Variable>(shared_from_this()) != nullptr)
	  {
		  return article? L"a variable" : L"variable";
	  }
	  if (std::dynamic_pointer_cast<Pick>(shared_from_this()) != nullptr)
	  {
		  return article? L"an array item": L"array item";
	  }
	  if (std::dynamic_pointer_cast<Mop>(shared_from_this()) != nullptr)
	  {
		  return article? L"monadic operator" : L"a monadic operator";
	  }
	  if (std::dynamic_pointer_cast<Dop>(shared_from_this()) != nullptr)
	  {
		  return article? L"dyadic operator" : L"a dyadic operator";
	  }
	  if (std::dynamic_pointer_cast<ArrFun>(shared_from_this()) != nullptr)
	  {
		  return article? L"an arrayified function": L"arrayified function";
	  }
	  if (std::dynamic_pointer_cast<APLMap::MapPointer>(shared_from_this()) != nullptr)
	  {
		  return article? L"a map item": L"map item";
	  }
	  if (std::dynamic_pointer_cast<BigValue>(shared_from_this()) != nullptr)
	  {
		  return article? L"a biginteger" : L"biginteger";
	  }
	  return L"some type that dzaima hasn't named in Obj.humanType ಠ_ಠ (class = " + getClass() + L")";
	}

	bool Obj::equals(std::any obj)
	{
	  return obj.type() == typeid(std::shared_ptr<Obj>) && equals(std::any_cast<std::shared_ptr<Obj>>(obj));
	}

	std::wstring Obj::name()
	{
	  return toString();
	}

	std::wstring Obj::toString()
	{
	  return humanType(false);
	}

	int Obj::hashCode()
	{
	  throw NYIError(StringHelper::wstring_to_string(L"hash not supported for " + shared_from_this(), shared_from_this()));
	}

	int Obj::actualHashCode()
	{
	  return __super::hashCode();
	}

	std::shared_ptr<Token> Obj::getToken()
	{
	  return token;
	}
}
