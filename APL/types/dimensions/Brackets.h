#pragma once

#include <APL/functions/builtins/fns/UpArrowBuiltin.h>
#include <APL/Callable.h>
#include <APL/Value.h>
#include <APL/Type.h>
#include <APL/Scope.h>
#include <APL/tokenizer/types/BracketTok.h>
#include <APL/Obj.h>
#include <string>
#include <vector>
#include <optional>
#include <cassert>
#include <memory>

namespace APL::types::dimensions
{

	using namespace APL;
	using namespace APL::tokenizer::types;
	using namespace APL::types;

	class Brackets : public Callable
	{

  public:
	  const std::shared_ptr<Value> val;

	  Brackets(std::shared_ptr<Value> val);

	  virtual std::optional<int> toInt();
	  virtual std::vector<int> toInts();

	  Type type() override;

	  virtual std::wstring toString();

	  static std::shared_ptr<Obj> of(std::shared_ptr<BracketTok> t, std::shared_ptr<Scope> sc);


	protected:
		std::shared_ptr<Brackets> shared_from_this()
		{
			return std::static_pointer_cast<Brackets>(Callable::shared_from_this());
		}
	};
}
