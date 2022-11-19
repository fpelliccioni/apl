#pragma once

#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/Builtin.h>
#include <APL/Num.h>
#include <APL/Value.h>
#include <APL/BigValue.h>
#include <APL/Obj.h>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class StileBuiltin : public Builtin
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
		  std::shared_ptr<Value> call(std::shared_ptr<BigValue> w) override;
	  };

  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

  private:
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
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a0, std::shared_ptr<Value> w0) override;



  private:
	  static const std::shared_ptr<D_NNeN> CPY_SGN;

  private:
	  class D_NNeNAnonymousInnerClass2 : public D_NNeN
	  {
	  public:
		  double on(double o, double n) override;
		  void on(std::vector<double> &res, double o, std::vector<double> &n) override;
		  void on(std::vector<double> &res, std::vector<double> &o, double n) override;
		  void on(std::vector<double> &res, std::vector<double> &o, std::vector<double> &n) override;
		  std::shared_ptr<Value> call(std::shared_ptr<BigValue> o, std::shared_ptr<BigValue> n) override;

	  protected:
		  std::shared_ptr<D_NNeNAnonymousInnerClass2> shared_from_this()
		  {
			  return std::static_pointer_cast<D_NNeNAnonymousInnerClass2>(D_NNeN::shared_from_this());
		  }
	  };
  public:
	  std::shared_ptr<Value> under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<StileBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<StileBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
