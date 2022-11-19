#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/tokenizer/Tokenizer.h>
#include <APL/tokenizer/types/BasicLines.h>
#include <APL/types/functions/builtins/dops/OverBuiltin.h>
#include <APL/types/Obj.h>
#include <APL/Sys.h>
#include <APL/types/Num.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <APL/types/Variable.h>
#include <APL/types/Primitive.h>
#include <APL/types/APLMap.h>
#include <APL/types/Fun.h>
#include <APL/types/functions/Mop.h>
#include <APL/types/functions/DerivedMop.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <helpers/tangible_exception_helper.h>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace APL { class Pr; }

namespace APL
{

	using namespace APL::errors;
	using BasicLines = APL::tokenizer::types::BasicLines;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::functions;
	using namespace APL::types::functions::builtins::fns;



	class Scope : public std::enable_shared_from_this<Scope>
	{
  public:
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: public final HashMap<String, Obj> vars = new HashMap<>();
	  std::unordered_map<std::wstring, std::shared_ptr<Obj>> vars = std::unordered_map<std::wstring, std::shared_ptr<Obj>>();
	  const std::shared_ptr<Sys> sys;
  private:
	  std::shared_ptr<Scope> parent = nullptr;
  public:
	  bool alphaDefined = false;
	  int IO = 0;
  private:
	  std::shared_ptr<Num> nIO;
  public:
	  std::shared_ptr<Random> rnd;
	  Scope(std::shared_ptr<Sys> sys);
	  Scope(std::shared_ptr<Scope> p);
  private:
	  std::shared_ptr<Scope> owner(const std::wstring &name);

  public:
	  virtual void update(const std::wstring &name, std::shared_ptr<Obj> val);
	  virtual void set(const std::wstring &name, std::shared_ptr<Obj> val);
	  virtual std::shared_ptr<Obj> get(const std::wstring &name);

  private:
	  class BuiltinAnonymousInnerClass : public Builtin
	  {
	  private:
		  std::shared_ptr<Scope> outerInstance;

	  public:
		  BuiltinAnonymousInnerClass(std::shared_ptr<Scope> outerInstance);

		  std::wstring repr() override;
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<BuiltinAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<BuiltinAnonymousInnerClass>(Builtin::shared_from_this());
		  }
	  };
  public:
	  virtual std::shared_ptr<Variable> getVar(const std::wstring &name);
	  virtual std::wstring toString();
  private:
	  std::wstring toString(const std::wstring &prep);

  public:
	  virtual double rand(double d);
	  virtual long long randLong();
	  virtual int rand(int n);

  public:
	  class GCLog : public Builtin
	  {
	public:
		std::wstring repr() override;

		GCLog(std::shared_ptr<Scope> sc);

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	public:
		class Logger : public Primitive
		{
	  public:
		  const std::wstring msg;
		  const std::shared_ptr<Scope> sc;
		  Logger(std::shared_ptr<Scope> sc, const std::wstring &s);

	  protected:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("deprecation") @Override protected void finalize()
//JAVA TO C++ CONVERTER WARNING: There is no equivalent in C++ to finalizer methods:
		  void finalize();
	  public:
		  std::wstring toString() override;

		  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;

		protected:
			std::shared_ptr<Logger> shared_from_this()
			{
				return std::static_pointer_cast<Logger>(Primitive::shared_from_this());
			}
		};

	  protected:
		  std::shared_ptr<GCLog> shared_from_this()
		  {
			  return std::static_pointer_cast<GCLog>(Builtin::shared_from_this());
		  }
	  };
  public:
	  class Timer : public Builtin
	  {
	public:
		const bool raw;
		std::wstring repr() override;
		Timer(std::shared_ptr<Scope> sc, bool raw);
		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
		std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<Timer> shared_from_this()
		  {
			  return std::static_pointer_cast<Timer>(Builtin::shared_from_this());
		  }
	  };
  public:
	  class Eraser : public Builtin
	  {
	public:
		std::wstring repr() override;
		Eraser(std::shared_ptr<Scope> sc);

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<Eraser> shared_from_this()
		  {
			  return std::static_pointer_cast<Eraser>(Builtin::shared_from_this());
		  }
	  };
  public:
	  class Delay : public Builtin {
	public:
		std::wstring repr() override;
		Delay(std::shared_ptr<Scope> sc);

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<Delay> shared_from_this() {
			  return std::static_pointer_cast<Delay>(Builtin::shared_from_this());
		  }
	  };
  public:
	  class UCS : public Builtin {
	public:
		std::wstring repr() override;
		UCS(std::shared_ptr<Scope> sc);

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	private:
		class NumMVAnonymousInnerClass : public std::enable_shared_from_this<NumMVAnonymousInnerClass>, public NumMV {
		private:
			std::shared_ptr<UCS> outerInstance;

		public:
			NumMVAnonymousInnerClass(std::shared_ptr<UCS> outerInstance);

			std::shared_ptr<Value> call(std::shared_ptr<Num> c) override;

			bool retNum() override;
		};

	public:
		std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<UCS> shared_from_this() {
			  return std::static_pointer_cast<UCS>(Builtin::shared_from_this());
		  }
	  };

  private:
	  class MapGen : public Builtin {
	public:
		std::wstring repr() override;

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

		std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<MapGen> shared_from_this() {
			  return std::static_pointer_cast<MapGen>(Builtin::shared_from_this());
		  }
	  };

  private:
	  class Optimizer : public Builtin {
	  private:
		  std::shared_ptr<Scope> outerInstance;

	public:
		std::wstring repr() override;
		Optimizer(std::shared_ptr<Scope> outerInstance, std::shared_ptr<Scope> sc);
		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<Optimizer> shared_from_this() {
			  return std::static_pointer_cast<Optimizer>(Builtin::shared_from_this());
		  }
	  };
  private:
	  class ClassGetter : public Builtin {
	public:
		std::wstring repr() override;
		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<ClassGetter> shared_from_this() {
			  return std::static_pointer_cast<ClassGetter>(Builtin::shared_from_this());
		  }
	  };

  private:
	  class Ex : public Builtin {
	public:
		std::wstring repr() override;
		Ex(std::shared_ptr<Scope> sc);

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
		std::shared_ptr<Obj> callObj(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<Ex> shared_from_this() {
			  return std::static_pointer_cast<Ex>(Builtin::shared_from_this());
		  }
	  };
  private:
	  class Lns : public Builtin {
	public:
		std::wstring repr() override;

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

		virtual std::wstring get(std::shared_ptr<APLMap> m, const std::wstring &key, const std::wstring &def);

		std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<Lns> shared_from_this() {
			  return std::static_pointer_cast<Lns>(Builtin::shared_from_this());
		  }
	  };


  private:
	  class Shell : public Fun {
	public:
		std::wstring repr() override;

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

		std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

		virtual std::shared_ptr<Value> exec(std::shared_ptr<Value> w, std::shared_ptr<File> f, std::vector<signed char> &inp, bool raw);
	private:
		std::vector<signed char> readAllBytes(std::shared_ptr<InputStream> is);

	  protected:
		  std::shared_ptr<Shell> shared_from_this() {
			  return std::static_pointer_cast<Shell>(Fun::shared_from_this());
		  }
	  };


  private:
	  class NC : public Fun {
	  private:
		  std::shared_ptr<Scope> outerInstance;

	public:
		std::wstring repr() override;

		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<NC> shared_from_this() {
			  return std::static_pointer_cast<NC>(Fun::shared_from_this());
		  }
	  };


  private:
	  class Hasher : public Builtin {
	public:
		std::wstring repr() override;
		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<Hasher> shared_from_this() {
			  return std::static_pointer_cast<Hasher>(Builtin::shared_from_this());
		  }
	  };
  private:
	  class Stdin : public Builtin {
	public:
		std::wstring repr() override;
		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  protected:
		  std::shared_ptr<Stdin> shared_from_this() {
			  return std::static_pointer_cast<Stdin>(Builtin::shared_from_this());
		  }
	  };

  private:
	  class Profiler : public Builtin {
	public:
		Profiler(std::shared_ptr<Scope> sc);

		static const std::unordered_map<std::wstring, std::shared_ptr<Pr>> pfRes;
		static std::shared_ptr<Obj> results();

		std::wstring repr() override;
		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
		std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	private:
		static std::shared_ptr<Pr> get(std::shared_ptr<Value> a, std::shared_ptr<Value> w);

	public:
		std::shared_ptr<Obj> callObj(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	public:
		class ProfilerOp : public Mop {

	  public:
		  ProfilerOp(std::shared_ptr<Scope> sc);

		  virtual std::shared_ptr<Pr> get(std::shared_ptr<Obj> f);

		  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

		  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

		  std::wstring repr() override;

		protected:
			std::shared_ptr<ProfilerOp> shared_from_this() {
				return std::static_pointer_cast<ProfilerOp>(Mop::shared_from_this());
			}
		};

	  protected:
		  std::shared_ptr<Profiler> shared_from_this() {
			  return std::static_pointer_cast<Profiler>(Builtin::shared_from_this());
		  }
	  };

  private:
	  class Pr : public std::enable_shared_from_this<Pr> {
	private:
		const std::shared_ptr<BasicLines> tok;
		int am = 0;
		double ms = 0.0;
		std::shared_ptr<Fun> fn;

	public:
		Pr(std::shared_ptr<BasicLines> tok);
	  };

  private:
	  class Big : public Fun {
	public:
		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	private:
		std::shared_ptr<Value> rec(std::shared_ptr<Value> w);

	public:
		std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;
	private:
		std::shared_ptr<Value> recN(std::shared_ptr<Value> w);
	public:
		std::wstring repr() override;

	  protected:
		  std::shared_ptr<Big> shared_from_this() {
			  return std::static_pointer_cast<Big>(Fun::shared_from_this());
		  }
	  };

  private:
	  class DR : public Fun {
	public:
		std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
		std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
		std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
		std::wstring repr() override;

	  protected:
		  std::shared_ptr<DR> shared_from_this() {
			  return std::static_pointer_cast<DR>(Fun::shared_from_this());
		  }
	  };
	};
}
