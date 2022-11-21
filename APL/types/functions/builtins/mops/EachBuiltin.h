#pragma once

#include <APL/Main.h>
#include <APL/types/functions/builtins/fns/LShoeBuiltin.h>
#include <APL/types/functions/Mop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedMop.h>
#include <APL/types/Fun.h>
#include <APL/types/Callable.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::mops
{

	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	// using namespace APL::types::functions;


	class EachBuiltin : public Mop
	{
  public:
	  std::string repr() override;



	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv) override;
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv) override;

	  std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> under(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv) override;

  private:
	  static void rec(std::shared_ptr<Fun> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w, int i, std::vector<std::shared_ptr<APL::types::Value>> &args, std::vector<std::shared_ptr<APL::types::Value>> &resPre, std::vector<std::shared_ptr<APL::types::Value>> &res);

  private:
	  class FunAnonymousInnerClass : public Fun
	  {
	  private:
		  std::shared_ptr<APL::types::Fun> aa;
		  std::shared_ptr<APL::types::Obj> o;
		  std::shared_ptr<APL::types::APL::types::Value> w;
		  int i = 0;
		  std::vector<std::shared_ptr<APL::types::APL::types::Value>> args;
		  std::vector<std::shared_ptr<APL::types::APL::types::Value>> resPre;
		  std::vector<std::shared_ptr<APL::types::APL::types::Value>> res;

	  public:
		  FunAnonymousInnerClass(std::shared_ptr<APL::types::Fun> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::APL::types::Value> w, int i, std::vector<std::shared_ptr<APL::types::APL::types::Value>> &args, std::vector<std::shared_ptr<APL::types::APL::types::Value>> &resPre, std::vector<std::shared_ptr<APL::types::APL::types::Value>> &res);

		  std::string repr() override;
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w1) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass>(Fun::shared_from_this());
		  }
	  };


  public:
	  std::shared_ptr<APL::types::Value> underW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv) override;

	  static std::shared_ptr<APL::types::Value> underW(std::shared_ptr<Fun> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<APL::types::Callable> blame);

  private:
	  static void rec(std::shared_ptr<Fun> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, int i, std::vector<std::shared_ptr<APL::types::Value>> &args, std::vector<std::shared_ptr<APL::types::Value>> &resPre, std::vector<std::shared_ptr<APL::types::Value>> &res);

  private:
	  class FunAnonymousInnerClass2 : public Fun
	  {
	  private:
		  std::shared_ptr<APL::types::Fun> aa;
		  std::shared_ptr<APL::types::Obj> o;
		  std::shared_ptr<APL::types::APL::types::Value> a;
		  std::shared_ptr<APL::types::APL::types::Value> w;
		  int i = 0;
		  std::vector<std::shared_ptr<APL::types::APL::types::Value>> args;
		  std::vector<std::shared_ptr<APL::types::APL::types::Value>> resPre;
		  std::vector<std::shared_ptr<APL::types::APL::types::Value>> res;

	  public:
		  FunAnonymousInnerClass2(std::shared_ptr<APL::types::Fun> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::APL::types::Value> a, std::shared_ptr<APL::types::APL::types::Value> w, int i, std::vector<std::shared_ptr<APL::types::APL::types::Value>> &args, std::vector<std::shared_ptr<APL::types::APL::types::Value>> &resPre, std::vector<std::shared_ptr<APL::types::APL::types::Value>> &res);

		  std::string repr() override;
		  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w1) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass2> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass2>(Fun::shared_from_this());
		  }
	  };

	protected:
		std::shared_ptr<EachBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<EachBuiltin>(Mop::shared_from_this());
		}
	};
}
