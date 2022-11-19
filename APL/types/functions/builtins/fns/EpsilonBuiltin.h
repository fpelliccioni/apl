#pragma once

#include <APL/errors/DomainError.h>
#include <APL/Builtin.h>
#include <APL/Value.h>
#include <APL/Obj.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	using ArrayList = java::util::ArrayList;


	class EpsilonBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

  private:
	  void rec(std::vector<std::shared_ptr<Value>> &arr, std::shared_ptr<Value> v);

  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;


	  std::shared_ptr<Value> under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w) override;
  private:
	  int copyIn(std::vector<std::shared_ptr<Value>> &res, std::vector<std::shared_ptr<Value>> &vs, std::shared_ptr<Value> orig, int s);

	protected:
		std::shared_ptr<EpsilonBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<EpsilonBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
