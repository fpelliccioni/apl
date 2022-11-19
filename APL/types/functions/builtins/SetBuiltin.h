#pragma once

#include <APL/errors/SyntaxError.h>
#include <APL/VarArr.h>
#include <APL/AbstractSet.h>
#include <APL/Obj.h>
#include <APL/Fun.h>
#include <APL/Value.h>
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
