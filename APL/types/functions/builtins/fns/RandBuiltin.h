#pragma once

#include <APL/Scope.h>
#include <APL/errors/DomainError.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Num.h>
#include <APL/types/Value.h>
#include <APL/types/BigValue.h>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using Scope = APL::Scope;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;


	class RandBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;

	  RandBuiltin(std::shared_ptr<Scope> sc);

  private:
	  const std::shared_ptr<NumMV> nf = std::make_shared<NumMVAnonymousInnerClass>();

  private:
	  class NumMVAnonymousInnerClass : public std::enable_shared_from_this<NumMVAnonymousInnerClass>, public NumMV
	  {
	  public:
		  std::shared_ptr<Value> call(std::shared_ptr<Num> v) override;
		  void call(std::vector<double> &res, std::vector<double> &a) override;
		  std::shared_ptr<Value> call(std::shared_ptr<BigValue> w) override;
	  };

  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<RandBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<RandBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
