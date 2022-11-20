#pragma once

#include <APL/types/Fun.h>
#include <APL/Scope.h>
#include <APL/types/Value.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;

	class RShoeBuiltin : public Fun
	{
  public:
	  std::wstring repr() override;

	  RShoeBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Obj> callObj(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
  private:
	  void replace(std::vector<std::shared_ptr<Value>> &vs, std::shared_ptr<Value> w, std::vector<int> &d, int i);

	protected:
		std::shared_ptr<RShoeBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<RShoeBuiltin>(Fun::shared_from_this());
		}
	};
}
