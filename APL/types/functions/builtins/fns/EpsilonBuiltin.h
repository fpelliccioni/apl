#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	// using ArrayList = java::util::ArrayList;


	class EpsilonBuiltin : public Builtin
	{
  public:
	  std::string repr() override;



	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

  private:
	  void rec(std::vector<std::shared_ptr<APL::types::Value>> &arr, std::shared_ptr<APL::types::Value> v);

  public:
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;


	  std::shared_ptr<APL::types::Value> under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w) override;
  private:
	  int copyIn(std::vector<std::shared_ptr<APL::types::Value>> &res, std::vector<std::shared_ptr<APL::types::Value>> &vs, std::shared_ptr<APL::types::Value> orig, int s);

	protected:
		std::shared_ptr<EpsilonBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<EpsilonBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
