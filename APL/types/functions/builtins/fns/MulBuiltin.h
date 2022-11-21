#pragma once

#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <APL/types/Num.h>
#include <APL/types/BigValue.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class MulBuiltin : public Builtin
	{
  public:
	  std::string repr() override;



	  std::shared_ptr<APL::types::Value> identity() override;

  private:
	  static const std::shared_ptr<NumMV> NF;

  private:
	  class NumMVAnonymousInnerClass : public std::enable_shared_from_this<NumMVAnonymousInnerClass>, public NumMV
	  {
	  public:
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<Num> w) override;
		  void call(std::vector<double> &res, std::vector<double> &a) override;
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::BigValue> w) override;
	  };
  public:
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

	  static const std::shared_ptr<D_NNeN> DNF;

  private:
	  class D_NNeNAnonymousInnerClass : public D_NNeN
	  {
	  public:
		  double on(double a, double w) override;
		  void on(std::vector<double> &res, double a, std::vector<double> &w) override;
		  void on(std::vector<double> &res, std::vector<double> &a, double w) override;
		  void on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w) override;
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w) override;

	  protected:
		  std::shared_ptr<D_NNeNAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<D_NNeNAnonymousInnerClass>(D_NNeN::shared_from_this());
		  }
	  };
  public:
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;


  private:
	  static const std::shared_ptr<D_NNeN> SET_SGN;

  private:
	  class D_NNeNAnonymousInnerClass2 : public D_NNeN
	  {
	  public:
		  double on(double o, double n) override;
		  void on(std::vector<double> &res, double o, std::vector<double> &n) override;
		  void on(std::vector<double> &res, std::vector<double> &o, double n) override;
		  void on(std::vector<double> &res, std::vector<double> &o, std::vector<double> &n) override;
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::BigValue> o, std::shared_ptr<APL::types::BigValue> n) override;

	  protected:
		  std::shared_ptr<D_NNeNAnonymousInnerClass2> shared_from_this()
		  {
			  return std::static_pointer_cast<D_NNeNAnonymousInnerClass2>(D_NNeN::shared_from_this());
		  }
	  };
  public:
	  std::shared_ptr<APL::types::Value> under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<MulBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<MulBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
