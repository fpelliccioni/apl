#pragma once

#include <APL/errors/SyntaxError.h>
#include <APL/types/functions/VarArr.h>
#include <APL/types/functions/builtins/AbstractSet.h>
#include <APL/types/Obj.h>
#include <APL/types/Fun.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins
{

	using namespace APL::types;

	class SetBuiltin : public AbstractSet
	{
  public:
	  static const std::shared_ptr<SetBuiltin> inst;

	  std::wstring toString() override;




	  std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> a, std::shared_ptr<Obj> w, bool update) override;

	  virtual std::shared_ptr<Obj> callObj(std::shared_ptr<Fun> f, std::shared_ptr<Obj> a, std::shared_ptr<Value> w);

	protected:
		std::shared_ptr<SetBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<SetBuiltin>(AbstractSet::shared_from_this());
		}
	};
}
