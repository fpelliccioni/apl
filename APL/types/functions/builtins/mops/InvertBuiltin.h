#pragma once

#include <APL/errors/NYIError.h>
#include <APL/Mop.h>
#include <APL/Obj.h>
#include <APL/Value.h>
#include <APL/DerivedMop.h>
#include <APL/Fun.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::mops
{

	using namespace APL::types;
	using namespace APL::types::functions;

	class InvertBuiltin : public Mop
	{ // separate ⍵-inverse (equal to f⍣¯1)

  public:
	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;
	  std::shared_ptr<Value> callInvW(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvA(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  static std::shared_ptr<Fun> invertM(std::shared_ptr<Fun> f);

  private:
	  class FunAnonymousInnerClass : public Fun
	  {
	  private:
		  std::shared_ptr<APL::types::Fun> f;

	  public:
		  FunAnonymousInnerClass(std::shared_ptr<APL::types::Fun> f);

		  std::wstring repr() override;
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass>(Fun::shared_from_this());
		  }
	  };
  public:
	  static std::shared_ptr<Fun> invertW(std::shared_ptr<Fun> f);

  private:
	  class FunAnonymousInnerClass2 : public Fun
	  {
	  private:
		  std::shared_ptr<APL::types::Fun> f;

	  public:
		  FunAnonymousInnerClass2(std::shared_ptr<APL::types::Fun> f);

		  std::wstring repr() override;
		  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

		  std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass2> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass2>(Fun::shared_from_this());
		  }
	  };
  public:
	  static std::shared_ptr<Fun> invertA(std::shared_ptr<Fun> f);

  private:
	  class FunAnonymousInnerClass3 : public Fun
	  {
	  private:
		  std::shared_ptr<APL::types::Fun> f;

	  public:
		  FunAnonymousInnerClass3(std::shared_ptr<APL::types::Fun> f);

		  std::wstring repr() override;
		  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

		  std::shared_ptr<Value> callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass3> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass3>(Fun::shared_from_this());
		  }
	  };

  public:
	  std::wstring repr() override;

	protected:
		std::shared_ptr<InvertBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<InvertBuiltin>(Mop::shared_from_this());
		}
	};
}
