#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Num.h>
#include <APL/types/Value.h>
#include <APL/types/BigValue.h>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class StarBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  static const std::shared_ptr<NumMV> NF;

  private:
	  class NumMVAnonymousInnerClass : public std::enable_shared_from_this<NumMVAnonymousInnerClass>, public NumMV
	  {
	  public:
		  std::shared_ptr<Value> call(std::shared_ptr<Num> w) override;
		  void call(std::vector<double> &res, std::vector<double> &a) override;
	  };
  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;

	  static const std::shared_ptr<D_NNeN> DNF;

  private:
	  class D_NNeNAnonymousInnerClass : public D_NNeN
	  {
	  public:
		  double on(double a, double w) override;
		  void on(std::vector<double> &res, double a, std::vector<double> &w) override;
		  void on(std::vector<double> &res, std::vector<double> &a, double w) override;
		  void on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w) override;
		  std::shared_ptr<Value> call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w) override;

	  protected:
		  std::shared_ptr<D_NNeNAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<D_NNeNAnonymousInnerClass>(D_NNeN::shared_from_this());
		  }
	  };
  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<StarBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<StarBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
