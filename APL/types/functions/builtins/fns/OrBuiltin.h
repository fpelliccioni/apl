#pragma once

#include <APL/types/arrs/BitArr.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <APL/types/BigValue.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	class OrBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> identity() override;

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

  private:
	  static const std::shared_ptr<D_BB> DBF;

  private:
	  class D_BBAnonymousInnerClass : public std::enable_shared_from_this<D_BBAnonymousInnerClass>, public D_BB
	  {
	  public:
		  std::shared_ptr<Value> call(bool a, std::shared_ptr<BitArr> w) override;
		  std::shared_ptr<Value> call(std::shared_ptr<BitArr> a, bool w) override;
		  std::shared_ptr<Value> call(std::shared_ptr<BitArr> a, std::shared_ptr<BitArr> w) override;
	  };
  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a0, std::shared_ptr<Value> w0) override;

	protected:
		std::shared_ptr<OrBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<OrBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
