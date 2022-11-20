#pragma once

#include <APL/types/arrs/BitArr.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/BigValue.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class NEBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



  private:
	  static const std::shared_ptr<D_NNeB> DNF;

  private:
	  class D_NNeBAnonymousInnerClass : public D_NNeB
	  {
	  public:
		  bool on(double a, double w) override;
		  void on(std::shared_ptr<BitArr::BA> res, double a, std::vector<double> &w);
		  void on(std::shared_ptr<BitArr::BA> res, std::vector<double> &a, double w);
		  void on(std::shared_ptr<BitArr::BA> res, std::vector<double> &a, std::vector<double> &w);
		  std::shared_ptr<Value> call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w) override;

	  protected:
		  std::shared_ptr<D_NNeBAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<D_NNeBAnonymousInnerClass>(D_NNeB::shared_from_this());
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
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<NEBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<NEBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
