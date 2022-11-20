#pragma once

#define _USE_MATH_DEFINES
#include <APL/types/functions/Builtin.h>
#include <APL/types/Num.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::errors;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	class TrigBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



  private:
	  static const std::shared_ptr<NumMV> NF;

  private:
	  class NumMVAnonymousInnerClass : public std::enable_shared_from_this<NumMVAnonymousInnerClass>, public NumMV
	  {
	  public:
		  std::shared_ptr<Value> call(std::shared_ptr<Num> w) override;
		  void call(std::vector<double> &res, std::vector<double> &a) override;
	  };
  private:
	  static const std::shared_ptr<NumMV> NFi;

  private:
	  class NumMVAnonymousInnerClass2 : public std::enable_shared_from_this<NumMVAnonymousInnerClass2>, public NumMV
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

	  protected:
		  std::shared_ptr<D_NNeNAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<D_NNeNAnonymousInnerClass>(D_NNeN::shared_from_this());
		  }
	  };
  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;


	  static const std::shared_ptr<D_NNeN> DNFi;

  private:
	  class D_NNeNAnonymousInnerClass2 : public D_NNeN
	  {
	  public:
		  double on(double a, double w) override;

	  protected:
		  std::shared_ptr<D_NNeNAnonymousInnerClass2> shared_from_this()
		  {
			  return std::static_pointer_cast<D_NNeNAnonymousInnerClass2>(D_NNeN::shared_from_this());
		  }
	  };
  public:
	  std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<TrigBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<TrigBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
