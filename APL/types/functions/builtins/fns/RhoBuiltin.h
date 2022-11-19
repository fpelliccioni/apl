#pragma once

#include <APL/Main.h>
#include <APL/Builtin.h>
#include <APL/Value.h>
#include <APL/Obj.h>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;



	class RhoBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;


	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  // public Value under(Obj o, Value w) {
	  //   Value v = o instanceof Fun? ((Fun) o).call(call(w)) : (Value) o;
	  //   int[] sh = v.asIntVec();
	  //
	  //   if (Arr.prod(sh) != w.ia) throw new DomainError("⍢⍴ expected equal amount of output & output items", this);
	  //   return w.ofShape(sh);
	  // }

	protected:
		std::shared_ptr<RhoBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<RhoBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
