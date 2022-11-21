#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/Scope.h>
#include <APL/types/Value.h>
#include <APL/types/arrs/BitArr.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	class NorBuiltin : public Builtin
	{
  public:
	  std::string repr() override;

	  NorBuiltin(std::shared_ptr<Scope> sc);

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
		  std::shared_ptr<APL::types::Value> call(bool a, std::shared_ptr<APL::types::arrs::BitArr> w) override;
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::arrs::BitArr> a, bool w) override;
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::arrs::BitArr> a, std::shared_ptr<APL::types::arrs::BitArr> w) override;
	  };

  public:
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<NorBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<NorBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
