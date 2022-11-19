#pragma once

#include <APL/tokenizer/Token.h>
#include <APL/Obj.h>
#include <APL/Scope.h>
#include <APL/tokenizer/types/DfnTok.h>
#include <APL/Type.h>
#include <APL/tokenizer/types/TokArr.h>
#include <APL/tokenizer/types/OpTok.h>
#include <APL/tokenizer/types/BacktickTok.h>
#include <string>
#include <helpers/tangible_exception_helper.h>
#include <memory>

namespace APL::types::functions::userDefined
{

	using namespace APL;
	using namespace APL::tokenizer::types;
	using Obj = APL::types::Obj;

	class UserDefined : public std::enable_shared_from_this<UserDefined>
	{
  public:
	  static std::shared_ptr<Obj> of(std::shared_ptr<DfnTok> ts, std::shared_ptr<Scope> sc);
  private:
	  template<typename T1>
	  static Type funType(std::shared_ptr<TokArr<T1>> i, bool first)
	  {
		Type type = Type::fn;
		if (!(std::dynamic_pointer_cast<DfnTok>(i) != nullptr) || first)
		{
			for (auto t : i->tokens)
			{
		  if (std::dynamic_pointer_cast<OpTok>(t) != nullptr)
		  {
			std::wstring op = (std::static_pointer_cast<OpTok>(t))->op;
			if (op == L"⍶")
			{
				type = Type::mop;
			}
			else if (op == L"⍹")
			{
				return Type::dop;
			}
		  }
//JAVA TO C++ CONVERTER TODO TASK: Java wildcard generics are not converted to C++:
//ORIGINAL LINE: else if (t instanceof TokArr<?>)
		  else if (std::dynamic_pointer_cast<TokArr<?>>(t) != nullptr)
		  {
//JAVA TO C++ CONVERTER TODO TASK: Java wildcard generics are not converted to C++:
//ORIGINAL LINE: Type n = funType((TokArr<?>) t, false);
			Type n = funType(std::static_pointer_cast<TokArr<?>>(t), false);
			if (n == Type::mop)
			{
				type = Type::mop;
			}
			else if (n.equals(Type::dop))
			{
				return Type::dop;
			}
		  }
		  else if (std::dynamic_pointer_cast<BacktickTok>(t) != nullptr)
		  {
			Type n = funType((std::static_pointer_cast<BacktickTok>(t))->value(), false);
			if (n == Type::mop)
			{
				type = Type::mop;
			}
			else if (n.equals(Type::dop))
			{
				return Type::dop;
			}
		  }
			}
		}
		return type;
	  }
	};
}
