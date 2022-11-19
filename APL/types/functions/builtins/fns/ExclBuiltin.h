#pragma once

#include <APL/errors/DomainError.h>
#include <APL/Builtin.h>
#include <APL/Num.h>
#include <APL/Value.h>
#include <APL/BigValue.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class ExclBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;


  private:
	  static const std::vector<double> cache;
	  private:
		  class StaticConstructor : public std::enable_shared_from_this<StaticConstructor>
		  {
		  public:
			  StaticConstructor();
		  };

	  private:
		  static ExclBuiltin::StaticConstructor staticConstructor;


	  static const std::shared_ptr<NumMV> NF;

  private:
	  class NumMVAnonymousInnerClass : public std::enable_shared_from_this<NumMVAnonymousInnerClass>, public NumMV
	  {
	  public:
		  std::shared_ptr<Value> call(std::shared_ptr<Num> w) override;
		  void call(std::vector<double> &res, std::vector<double> &a) override;
		  std::shared_ptr<Value> call(std::shared_ptr<BigValue> w) override;
	  };

  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a0, std::shared_ptr<Value> w0) override;

	protected:
		std::shared_ptr<ExclBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<ExclBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
