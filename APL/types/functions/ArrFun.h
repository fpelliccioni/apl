#pragma once

#include <APL/errors/DomainError.h>
#include <APL/tokenizer/types/BacktickTok.h>
#include <APL/arrs/SingleItemArr.h>
#include <APL/Primitive.h>
#include <APL/Obj.h>
#include <APL/Fun.h>
#include <APL/Scope.h>
#include <APL/Value.h>
#include <string>
#include <vector>
#include <helpers/tangible_exception_helper.h>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions
{

	using namespace APL;
	using BacktickTok = APL::tokenizer::types::BacktickTok;
	using namespace APL::types;

	class ArrFun : public Primitive
	{

  private:
	  const std::shared_ptr<Obj> f;

  public:
	  ArrFun(std::shared_ptr<Fun> f);

	  ArrFun(std::shared_ptr<BacktickTok> t, std::shared_ptr<Scope> sc);

	  virtual std::shared_ptr<Obj> obj();

	  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;

	  virtual std::wstring toString();

	  virtual int hashCode();

	  virtual bool equals(std::shared_ptr<Obj> o);

	protected:
		std::shared_ptr<ArrFun> shared_from_this()
		{
			return std::static_pointer_cast<ArrFun>(Primitive::shared_from_this());
		}
	};
}
