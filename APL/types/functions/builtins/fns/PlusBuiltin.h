#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <APL/types/BigValue.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class PlusBuiltin : public Builtin
	{
  public:
	  std::string repr() override;



	  std::shared_ptr<APL::types::Value> identity() override;

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
	  std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Value> w) override;
	  std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<PlusBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<PlusBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
