//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/Scope.h>
#include <APL/types/BigValue.h>
#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/functions/builtins/fns/UTackBuiltin.h>
#include <APL/types/arrs/BitArr copy 2.h>
#include <APL/types/arrs/BitArr copy.h>
#include <APL/types/arrs/BitArr.h>
#include <APL/types/arrs/SingleItemArr.h>
#include <APL/types/Null.h>
#include <APL/types/arrs/DoubleArr copy.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/Char.h>
#include <APL/types/StrMap.h>
#include <APL/errors/RankError.h>
#include <APL/errors/LengthError.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/Arr copy.h>
#include <APL/types/Arr.h>
#include <APL/types/arrs/HArr.h>
#include <APL/types/functions/Dop.h>
#include <APL/types/functions/ArrFun.h>
#include <APL/errors/NYIError.h>
#include <APL/types/functions/builtins/fns/ReverseBuiltin.h>

namespace APL {
	using namespace APL::errors;
	using Tokenizer = APL::tokenizer::Tokenizer;
	using BasicLines = APL::tokenizer::types::BasicLines;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::functions;
	using OverBuiltin = APL::types::functions::builtins::dops::OverBuiltin;
	using namespace APL::types::functions::builtins::fns;
	using StandardCharsets = java::nio::charset::StandardCharsets;

	Scope::FunAnonymousInnerClass::FunAnonymousInnerClass(std::shared_ptr<DR> outerInstance) {
		this->outerInstance = outerInstance;
	}

	std::wstring Scope::FunAnonymousInnerClass::repr() {
		return L"";
	}

	std::shared_ptr<Value> Scope::FunAnonymousInnerClass::call(std::shared_ptr<Value> w) {
	  return std::make_shared<Num>(Double::longBitsToDouble((std::static_pointer_cast<BigValue>(UTackBuiltin::on(BigValue::TWO, w, DR::this)))->longValue()));
	}

	Scope::FunAnonymousInnerClass2::FunAnonymousInnerClass2(std::shared_ptr<DR> outerInstance) {
		this->outerInstance = outerInstance;
	}

	std::wstring Scope::FunAnonymousInnerClass2::repr() {
		return L"";
	}

	std::shared_ptr<Value> Scope::FunAnonymousInnerClass2::call(std::shared_ptr<Value> w) {
	  return std::make_shared<Num>(Double::longBitsToDouble((std::static_pointer_cast<BigValue>(w))->longValue()));
	}

	Scope::FunAnonymousInnerClass3::FunAnonymousInnerClass3(std::shared_ptr<DR> outerInstance) {
		this->outerInstance = outerInstance;
	}

	std::wstring Scope::FunAnonymousInnerClass3::repr() {
		return L"";
	}

	std::shared_ptr<Value> Scope::FunAnonymousInnerClass3::call(std::shared_ptr<Value> w) {
	  return std::make_shared<BitArr>(std::vector<long long>{Long::reverse(Double::doubleToRawLongBits(w->asDouble()))}, std::vector<int>{64});
	}

	Scope::FunAnonymousInnerClass4::FunAnonymousInnerClass4(std::shared_ptr<DR> outerInstance) {
		this->outerInstance = outerInstance;
	}

	std::wstring Scope::FunAnonymousInnerClass4::repr() {
		return L"";
	}

	std::shared_ptr<Value> Scope::FunAnonymousInnerClass4::call(std::shared_ptr<Value> w) {
	  return std::make_shared<BigValue>(Double::doubleToRawLongBits(w->asDouble()));
	}

	Scope::Scope(std::shared_ptr<Sys> sys) : sys(sys) {
	  IO = 1;
	  nIO = Num::ONE;
	  rnd = std::make_shared<Random>();
	}

	Scope::Scope(std::shared_ptr<Scope> p) : sys(p->sys) {
	  parent = p;
	  IO = p->IO;
	  nIO = p->nIO;
	  rnd = p->rnd;
	}

	std::shared_ptr<Scope> Scope::owner(const std::wstring &name) {
	  if (vars.find(name) != vars.end()) {
		  return shared_from_this();
	  } else if (parent == nullptr) {
		  return nullptr;
	  } else {
		  return parent->owner(name);
	  }
	}

	void Scope::update(const std::wstring &name, std::shared_ptr<Obj> val) {
	  std::shared_ptr<Scope> sc = owner(name);
	  if (sc == nullptr) {
		  sc = shared_from_this();
	  }
	  sc->set(name, val);
	}

	void Scope::set(const std::wstring &name, std::shared_ptr<Obj> val) {
	  if (name[0] == L'⎕') {
//JAVA TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
//		switch (name)
//ORIGINAL LINE: case "⎕IO":
		if (name == L"⎕IO") {
			int tIO = (std::static_pointer_cast<Value>(val))->asInt();
			if (tIO != 0 && tIO != 1) {
				throw DomainError(L"⎕IO should be 0 or 1", val);
			}
			IO = tIO;
			nIO = IO == 0? Num::ZERO : Num::ONE;
		}
//ORIGINAL LINE: case "⎕BOXSIMPLE":
		else if (name == L"⎕BOXSIMPLE") {
			Main::enclosePrimitives = (std::static_pointer_cast<Value>(val))->asInt() == 1;
		}
//ORIGINAL LINE: case "⎕VI":
		else if (name == L"⎕VI") {
			Main::vind = Main::bool_Keyword(val);
		}
//ORIGINAL LINE: case "⎕RL":
		else if (name == L"⎕RL") {
			rnd = std::make_shared<Random>((std::static_pointer_cast<Value>(val))->asInt());
		}
//ORIGINAL LINE: case "⎕PP":
		else if (name == L"⎕PP") {
			if (std::dynamic_pointer_cast<Primitive>(val) != nullptr) {
			  Num::setPrecision((std::static_pointer_cast<Value>(val))->asInt());
			} else {
			  std::vector<int> args = (std::static_pointer_cast<Value>(val))->asIntVec();
			  if (args.size() == 3) {
				  Num::setPrecision(args[0], args[1], args[2]);
			  } else {
				  throw DomainError(L"⎕PP expected either a scalar number or array of 3 integers as ⍵", val);
			  }
			}
		} else {
			throw DomainError(StringHelper::wstring_to_string(L"setting unknown quad " + name));
		}
	  } else {
		  vars.emplace(name, val);
	  }
	}

	std::shared_ptr<Obj> Scope::get(const std::wstring &name) {
	  if (StringHelper::startsWith(name, L"⎕")) {
//JAVA TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
//		switch (name)
//ORIGINAL LINE: case "⎕MILLIS":
		if (name == L"⎕MILLIS") {
			  return std::make_shared<Num>(System::currentTimeMillis() - Main::startingMillis);
		}
//ORIGINAL LINE: case "⎕TIME":
		else if (name == L"⎕TIME") {
			  return std::make_shared<Timer>(shared_from_this(), true);
		}
//ORIGINAL LINE: case "⎕HTIME":
		else if (name == L"⎕HTIME") {
			  return std::make_shared<Timer>(shared_from_this(), false);
		}
//ORIGINAL LINE: case "⎕EX":
		else if (name == L"⎕EX") {
			  return std::make_shared<Ex>(shared_from_this());
		}
//ORIGINAL LINE: case "⎕LNS":
		else if (name == L"⎕LNS") {
			  return std::make_shared<Lns>();
		}
//ORIGINAL LINE: case "⎕SH":
		else if (name == L"⎕SH") {
			  return std::make_shared<Shell>();
		}
//ORIGINAL LINE: case "⎕NC":
		else if (name == L"⎕NC") {
			  return std::make_shared<NC>(shared_from_this(), shared_from_this());
		}
//ORIGINAL LINE: case "⎕A":
		else if (name == L"⎕A") {
			  return Main::alphabet;
		}
//ORIGINAL LINE: case "⎕AV":
		else if (name == L"⎕AV") {
			  return Main::toAPL(Main::CODEPAGE);
		}
//ORIGINAL LINE: case "⎕D":
		else if (name == L"⎕D") {
			  return Main::digits;
		}
//ORIGINAL LINE: case "⎕L":
		else if (name == L"⎕L" || name == L"⎕LA") {
			  return Main::lowercaseAlphabet;
		}
//ORIGINAL LINE: case "⎕ERASE":
		else if (name == L"⎕ERASE") {
			  return std::make_shared<Eraser>(shared_from_this());
		}
//ORIGINAL LINE: case "⎕GC":
		else if (name == L"⎕GC") {
			  System::gc();
			  return std::make_shared<Num>(Runtime::getRuntime().totalMemory() - Runtime::getRuntime().freeMemory());
		}
//ORIGINAL LINE: case "⎕GCLOG":
		else if (name == L"⎕GCLOG") {
			  return std::make_shared<GCLog>(shared_from_this());
		}
//ORIGINAL LINE: case "⎕NULL":
		else if (name == L"⎕NULL") {
			  return Null::NULL;
		}
//ORIGINAL LINE: case "⎕MAP":
		else if (name == L"⎕MAP" || name == L"⎕NS") {
		  return std::make_shared<MapGen>();
		}
//ORIGINAL LINE: case "⎕DL":
		else if (name == L"⎕DL") {
			  return std::make_shared<Delay>(shared_from_this());
		}
//ORIGINAL LINE: case "⎕DR":
		else if (name == L"⎕DR") {
			  return std::make_shared<DR>();
		}
//ORIGINAL LINE: case "⎕UCS":
		else if (name == L"⎕UCS") {
			  return std::make_shared<UCS>(shared_from_this());
		}
//ORIGINAL LINE: case "⎕HASH":
		else if (name == L"⎕HASH") {
			  return std::make_shared<Hasher>();
		}
//ORIGINAL LINE: case "⎕IO":
		else if (name == L"⎕IO") {
			  return nIO;
		}
//ORIGINAL LINE: case "⎕VI":
		else if (name == L"⎕VI") {
			  return Main::vind? Num::ONE : Num::ZERO;
		}
//ORIGINAL LINE: case "⎕BOXSIMPLE":
		else if (name == L"⎕BOXSIMPLE") {
			  return Main::enclosePrimitives? Num::ONE : Num::ZERO;
		}
//ORIGINAL LINE: case "⎕CLASS":
		else if (name == L"⎕CLASS") {
			  return std::make_shared<ClassGetter>();
		}
//ORIGINAL LINE: case "⎕PP":
		else if (name == L"⎕PP") {
			  return std::make_shared<DoubleArr>(std::vector<double> {Num::pp, Num::sEr, Num::eEr});
		}
//ORIGINAL LINE: case "⎕PFX":
		else if (name == L"⎕PFX") {
			  return std::make_shared<Profiler>(shared_from_this());
		}
//ORIGINAL LINE: case "⎕PFO":
		else if (name == L"⎕PFO") {
			  return std::make_shared<Profiler::ProfilerOp>(shared_from_this());
		}
//ORIGINAL LINE: case "⎕PFR":
		else if (name == L"⎕PFR") {
			  return Profiler::results();
		}
//ORIGINAL LINE: case "⎕STDIN":
		else if (name == L"⎕STDIN") {
			  return std::make_shared<Stdin>();
		}
//ORIGINAL LINE: case "⎕BIG":
		else if (name == L"⎕BIG") {
			  return std::make_shared<Big>();
		}
//ORIGINAL LINE: case "⎕U":
		else if (name == L"⎕U") {
			  return std::make_shared<BuiltinAnonymousInnerClass>(shared_from_this());
		}
//ORIGINAL LINE: case "⎕OPT":
		else if (name == L"⎕OPT" || name == L"⎕OPTIMIZE") {
			return std::make_shared<Optimizer>(shared_from_this(), shared_from_this(), shared_from_this());
		}
	  }
	  std::shared_ptr<Obj> f = vars[name];
	  if (f == nullptr) {
		if (parent == nullptr) {
			return nullptr;
		} else {
			return parent->get(name);
		}
	  } else {
		  return f;
	  }
	}

	Scope::BuiltinAnonymousInnerClass::BuiltinAnonymousInnerClass(std::shared_ptr<Scope> outerInstance) : outerInstance(outerInstance) {
	}

	std::wstring Scope::BuiltinAnonymousInnerClass::repr() {
		return L"⎕U";
	}

	std::shared_ptr<Value> Scope::BuiltinAnonymousInnerClass::call(std::shared_ptr<Value> w) {
	  outerInstance->sys->ucmd(w->asString());
	  return nullptr;
	}

	std::shared_ptr<Variable> Scope::getVar(const std::wstring &name) {
	  return std::make_shared<Variable>(shared_from_this(), name);
	}

	std::wstring Scope::toString() {
	  return toString(L"");
	}

	std::wstring Scope::toString(const std::wstring &prep) {
	  std::shared_ptr<StringBuilder> res = std::make_shared<StringBuilder>(L"{\n");
	  std::wstring cp = prep + L"  ";
	  for (auto n : vars) {
		  res->append(cp)->append(n.first)->append(L" ← ")->append(get(n.first))->append(L"\n");
	  }
	  if (parent != nullptr) {
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
		  res->append(cp)->append(L"parent: ")->append(parent->toString(cp));
	  }
	  res->append(prep)->append(L"}\n");
	  return res->toString();
	}

	double Scope::rand(double d) {
	  return rnd->nextDouble() * d;
	} // with ⎕IO←0

	long long Scope::randLong() {
	  return rnd->nextLong();
	} // with ⎕IO←0

	int Scope::rand(int n) {
	  return rnd->nextInt(n);
	} // with ⎕IO←0

	std::wstring Scope::GCLog::repr() {
	  return L"⎕GCLOG";
	}

	Scope::GCLog::GCLog(std::shared_ptr<Scope> sc) : Builtin(sc) {
	}

	std::shared_ptr<Value> Scope::GCLog::call(std::shared_ptr<Value> w) {
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  return std::make_shared<Logger>(sc, w->toString());
	}

	Scope::GCLog::Logger::Logger(std::shared_ptr<Scope> sc, const std::wstring &s) : msg(s), sc(sc) {
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("deprecation") @Override protected void finalize()
//JAVA TO C++ CONVERTER WARNING: There is no equivalent in C++ to finalizer methods:
	void Scope::GCLog::Logger::finalize() {
	  sc->sys.println(msg + L" was GCed");
	}

	std::wstring Scope::GCLog::Logger::toString() {
	  return L"⎕GCLOG[" + msg + L"]";
	}

	std::shared_ptr<Value> Scope::GCLog::Logger::ofShape(std::vector<int> &sh) {
	  return SingleItemArr::maybe(shared_from_this(), sh);
	}

	std::wstring Scope::Timer::repr() {
	  return L"⎕TIME";
	}

	Scope::Timer::Timer(std::shared_ptr<Scope> sc, bool raw) : Builtin(sc), raw(raw) {
	}

	std::shared_ptr<Value> Scope::Timer::call(std::shared_ptr<Value> w) {
	  return call(Num::ONE, w);
	}

	std::shared_ptr<Value> Scope::Timer::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) {
	  std::vector<int> options = a->asIntVec();
	  int n = options[0];

	  bool separate = false;
	  if (options.size() >= 2) {
		  separate = options[1] == 1;
	  }


	  std::wstring test = w->asString();

	  std::shared_ptr<BasicLines> testTokenized = Tokenizer::tokenize(test);

	  if (separate) {
		std::vector<double> r(n);
		for (int i = 0; i < n; i++) {
		  long long start = System::nanoTime();
		  Main::execLines(testTokenized, sc);
		  long long end = System::nanoTime();
		  r[i] = end - start;
		}
		return std::make_shared<DoubleArr>(r);
	  } else {
		long long start = System::nanoTime();
		for (int i = 0; i < n; i++) {
			Main::execLines(testTokenized, sc);
		}
		long long end = System::nanoTime();
		if (raw) {
		  return std::make_shared<Num>((end - start) / n);
		} else {
		  double t = end - start;
		  t /= n;
		  if (t < 1000) {
			  return Main::toAPL(std::make_shared<Num>(t) + L" nanos");
		  }
		  t /= 1e6;
		  if (t > 500) {
			  return Main::toAPL(std::make_shared<Num>(t / 1000.0) + L" seconds");
		  }
		  return Main::toAPL(std::make_shared<Num>(t) + L" millis");
		}
	  }
	}

	std::wstring Scope::Eraser::repr() {
	  return L"⎕ERASE";
	}

	Scope::Eraser::Eraser(std::shared_ptr<Scope> sc) : Builtin(sc) {
	}

	std::shared_ptr<Value> Scope::Eraser::call(std::shared_ptr<Value> w) {
	  sc->set(w->asString(), nullptr);
	  return w;
	}

	std::wstring Scope::Delay::repr() {
	  return L"⎕DL";
	}

	Scope::Delay::Delay(std::shared_ptr<Scope> sc) : Builtin(sc) {
	}

	std::shared_ptr<Value> Scope::Delay::call(std::shared_ptr<Value> w) {
	  long long nsS = System::nanoTime();
	  double ms = w->asDouble() * 1000;
	  int ns = static_cast<int>((ms % 1) * 1000000);
	  try {
		Thread::sleep(static_cast<int>(ms), ns);
	  } catch (const InterruptedException &ignored) {
	  }
	  return std::make_shared<Num>((System::nanoTime() - nsS) / 1000000000.0);
	}

	std::wstring Scope::UCS::repr() {
	  return L"⎕UCS";
	}

	Scope::UCS::UCS(std::shared_ptr<Scope> sc) : Builtin(sc) {
	}

	std::shared_ptr<Value> Scope::UCS::call(std::shared_ptr<Value> w) {
	  return numChrM(std::make_shared<NumMVAnonymousInnerClass>(shared_from_this())
	 , [&] (std::any c) {
	 Num::of(c::chr);
	 }, w);
	}

	Scope::UCS::NumMVAnonymousInnerClass::NumMVAnonymousInnerClass(std::shared_ptr<UCS> outerInstance) : outerInstance(outerInstance) {
	}

	std::shared_ptr<Value> Scope::UCS::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> c) {
	  return Char::of(static_cast<wchar_t>(c->asInt()));
	}

	bool Scope::UCS::NumMVAnonymousInnerClass::retNum() {
	  return false;
	}

	std::shared_ptr<Value> Scope::UCS::callInv(std::shared_ptr<Value> w) {
	  return call(w);
	}

	std::wstring Scope::MapGen::repr() {
	  return L"⎕MAP";
	}

	std::shared_ptr<Value> Scope::MapGen::call(std::shared_ptr<Value> w) {
	  if (std::dynamic_pointer_cast<StrMap>(w) != nullptr) {
		std::shared_ptr<StrMap> wm = std::static_pointer_cast<StrMap>(w);
		// Scope sc;
		// HashMap<String, Obj> vals;
		// if (wm.sc == null) {
		//   sc = null;
		//   vals = new HashMap<>(wm.vals);
		// } else {
		//   sc = new Scope(wm.sc.parent);
		//   sc.vars.putAll(wm.vals);
		//   vals = sc.vars;
		// }
		// return new StrMap(sc, vals);
		return std::make_shared<StrMap>(std::unordered_map<>(wm->vals));
	  }
	  auto map = std::make_shared<StrMap>();
	  for (auto v : w) {
		if (v->rank != 1 || v->ia != 2) {
			throw RankError(L"⎕map: input pairs should be 2-item vectors", shared_from_this(), v);
		}
		map[v[0]] = v[1];
	  }
	  return map;
	}

	std::shared_ptr<Value> Scope::MapGen::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) {
	  if (a->rank != 1) {
		  throw RankError(L"rank of ⍺ ≠ 1", shared_from_this(), a);
	  }
	  if (w->rank != 1) {
		  throw RankError(L"rank of ⍵ ≠ 1", shared_from_this(), w);
	  }
	  if (a->ia != w->ia) {
		  throw LengthError(L"both sides lengths should match", shared_from_this(), w);
	  }
	  auto map = std::make_shared<StrMap>();
	  for (int i = 0; i < a->ia; i++) {
		map[a[i]] = w[i];
	  }
	  return map;
	}

	std::wstring Scope::Optimizer::repr() {
	  return L"⎕OPT";
	}

	Scope::Optimizer::Optimizer(std::shared_ptr<Scope> outerInstance, std::shared_ptr<Scope> sc) : Builtin(sc), outerInstance(outerInstance) {
	}

	std::shared_ptr<Value> Scope::Optimizer::call(std::shared_ptr<Value> w) {
	  std::wstring name = w->asString();
	  if (!(std::dynamic_pointer_cast<Value>(outerInstance->get(name)) != nullptr)) {
		  return Num::MINUS_ONE;
	  }
	  std::shared_ptr<Value> v = std::static_pointer_cast<Value>(outerInstance->get(name));
	  std::shared_ptr<Value> optimized = v->squeeze();
	  if (v == optimized) {
		  return Num::ZERO;
	  }
	  outerInstance->update(name, optimized);
	  return Num::ONE;
	}

	std::wstring Scope::ClassGetter::repr() {
	  return L"⎕CLASS";
	}

	std::shared_ptr<Value> Scope::ClassGetter::call(std::shared_ptr<Value> w) {
	  return std::make_shared<ChrArr>(w->getClass().getCanonicalName());
	}

	std::wstring Scope::Ex::repr() {
	  return L"⎕EX";
	}

	Scope::Ex::Ex(std::shared_ptr<Scope> sc) : Builtin(sc) {
	}

	std::shared_ptr<Value> Scope::Ex::call(std::shared_ptr<Value> w) {
	  std::shared_ptr<Obj> o = callObj(w);
	  if (std::dynamic_pointer_cast<Value>(o) != nullptr) {
		  return std::static_pointer_cast<Value>(o);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Was expected to give array, got " + o->humanType(true), shared_from_this()));
	}

	std::shared_ptr<Obj> Scope::Ex::callObj(std::shared_ptr<Value> w) {
	  std::wstring path = w->asString();
	  return Main::exec(Main::readFile(path), sc);
	}

	std::wstring Scope::Lns::repr() {
	  return L"⎕LNS";
	}

	std::shared_ptr<Value> Scope::Lns::call(std::shared_ptr<Value> w) {
	  std::wstring path = w->asString();
	  std::vector<std::wstring> a = Main::readFile(path).split(L"\n");
	  std::vector<std::shared_ptr<Value>> o(a.size());
	  for (int i = 0; i < a.size(); i++) {
		o[i] = Main::toAPL(a[i]);
	  }
	  return Arr::create(o);
	}

	std::wstring Scope::Lns::get(std::shared_ptr<APLMap> m, const std::wstring &key, const std::wstring &def) {
	  std::shared_ptr<Value> got = std::static_pointer_cast<Value>(m->getRaw(key));
	  if (got != Null::NULL) {
		  return got->asString();
	  }
	  return def;
	}

	std::shared_ptr<Value> Scope::Lns::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) {
	  if (std::dynamic_pointer_cast<APLMap>(a) != nullptr) {
		try {
		  std::shared_ptr<URL> url = std::make_shared<URL>(w->asString());
		  std::shared_ptr<HttpURLConnection> conn = std::static_pointer_cast<HttpURLConnection>(url->openConnection());
		  std::shared_ptr<APLMap> m = std::static_pointer_cast<APLMap>(a);
		  std::wstring content = get(m, L"content", L"");
		  conn->setRequestMethod(get(m, L"method", L"POST"));

		  conn->setRequestProperty(L"Content-Type", get(m, L"type", L"POST"));
		  conn->setRequestProperty(L"Content-Language", get(m, L"language", L"en-US"));
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
		  conn->setRequestProperty(L"Content-Length", Integer::toString(content.length()));

		  std::shared_ptr<Obj> eo = m->getRaw(L"e");
		  if (eo != Null::NULL) {
			std::shared_ptr<APLMap> e = std::static_pointer_cast<APLMap>(eo);
			for (auto k : e->allKeys()) {
			  std::shared_ptr<Value> v = std::static_pointer_cast<Value>(e->getRaw(k));
			  conn->setRequestProperty(k->asString(), v->asString());
			}
		  }

		  std::shared_ptr<Obj> cache = m->getRaw(L"cache");
		  conn->setUseCaches(cache != Null::NULL && Main::bool_Keyword(cache));
		  conn->setDoOutput(true);

		  if (content.length() != 0) {
			std::shared_ptr<DataOutputStream> os = std::make_shared<DataOutputStream>(conn->getOutputStream());
			os->writeBytes(content);
			os->close();
		  }


		  std::shared_ptr<InputStream> is = conn->getInputStream();
		  std::vector<std::shared_ptr<Value>> vs;
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (BufferedReader rd = new BufferedReader(new InputStreamReader(is)))
		  {
			  BufferedReader rd = BufferedReader(std::make_shared<InputStreamReader>(is));
			std::wstring ln;
			while ((ln = rd.readLine()) != L"") {
				vs.push_back(Main::toAPL(ln));
			}
		  }
		  return std::make_shared<HArr>(vs);
		} catch (const MalformedURLException &e) {
		  throw DomainError(StringHelper::wstring_to_string(L"bad URL: " + e->getMessage(), shared_from_this()));
		} catch (const ProtocolException &e) {
		  throw DomainError(StringHelper::wstring_to_string(L"ProtocolException: " + e->getMessage(), shared_from_this()));
		} catch (const IOException &e) {
		  throw DomainError(StringHelper::wstring_to_string(L"IOException: " + e->getMessage(), shared_from_this()));
		}
	  } else {
		std::wstring p = a->asString();
		std::wstring s = w->asString();
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (PrintWriter pw = new PrintWriter(p))
		{
			PrintWriter pw = PrintWriter(p);
			try {
			  pw.write(s);
			} catch (const FileNotFoundException &e) {
			  throw DomainError(StringHelper::wstring_to_string(L"File " + p + L" not found: " + e->getMessage(), shared_from_this()));
			}
		}
		return w;
	  }
	}

	std::wstring Scope::Shell::repr() {
	  return L"⎕SH";
	}

	std::shared_ptr<Value> Scope::Shell::call(std::shared_ptr<Value> w) {
	  return exec(w, nullptr, std::vector<signed char>(), false);
	}

	std::shared_ptr<Value> Scope::Shell::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) {
	  std::shared_ptr<APLMap> m = std::static_pointer_cast<APLMap>(a);

	  std::shared_ptr<File> dir = nullptr;
	  std::shared_ptr<Obj> diro = m->getRaw(L"dir");
	  if (diro != Null::NULL) {
		  dir = std::make_shared<File>((std::static_pointer_cast<Value>(diro))->asString());
	  }

	  std::vector<signed char> inp;
	  std::shared_ptr<Obj> inpo = m->getRaw(L"inp");
	  if (inpo != Null::NULL) {
		std::shared_ptr<Value> inpv = std::static_pointer_cast<Value>(inpo);
		if (inpv->ia > 0) {
		  if (std::dynamic_pointer_cast<Char>(inpv->first()) != nullptr) {
			  inp = inpv->asString().getBytes(StandardCharsets::UTF_8);
		  } else {
			inp = std::vector<signed char>(inpv->ia);
			std::vector<double> ds = inpv->asDoubleArr();
			for (int i = 0; i < ds.size(); i++) {
				inp[i] = static_cast<signed char>(ds[i]);
			}
		  }
		}
	  }

	  bool raw = false;
	  std::shared_ptr<Obj> rawo = m->getRaw(L"raw");
	  if (rawo != Null::NULL) {
		  raw = Main::bool_Keyword(rawo);
	  }

	  return exec(w, dir, inp, raw);
	}

	std::shared_ptr<Value> Scope::Shell::exec(std::shared_ptr<Value> w, std::shared_ptr<File> f, std::vector<signed char> &inp, bool raw) {
	  try {
		std::shared_ptr<Process> p;
		if (std::dynamic_pointer_cast<Char>(w[0]) != nullptr) {
		  std::wstring cmd = w->asString();
		  p = Runtime::getRuntime().exec(cmd, std::vector<std::wstring>(0), f);
		} else {
		  std::vector<std::wstring> parts(w->ia);
		  for (int i = 0; i < parts.size(); i++) {
			parts[i] = w[i].asString();
		  }
		  p = Runtime::getRuntime().exec(parts, std::vector<std::wstring>(0), f);
		}
		if (!inp.empty()) {
			p->getOutputStream().write(inp);
		}
		p->getOutputStream()->close();
		std::vector<signed char> out = readAllBytes(p->getInputStream());
		std::vector<signed char> err = readAllBytes(p->getErrorStream());
		std::shared_ptr<Num> ret = Num::of(p->waitFor());
		if (raw) {
			return std::make_shared<HArr>(std::vector<std::shared_ptr<Value>>{ret, std::make_shared<DoubleArr>(out), std::make_shared<DoubleArr>(err)});
		} else {
			return std::make_shared<HArr>(std::vector<std::shared_ptr<Value>>{ret, Main::toAPL(std::wstring(out, StandardCharsets::UTF_8)), Main::toAPL(std::wstring(err, StandardCharsets::UTF_8))});
		}
	  } catch (const std::runtime_error &e) {
		e.printStackTrace();
		return Null::NULL;
	  }
	}

	std::vector<signed char> Scope::Shell::readAllBytes(std::shared_ptr<InputStream> is) {
	  try {
		std::vector<signed char> res(512);
		int used = 0;
		while (true) {
		  while (used < res.size()) {
			int n = is->read(res, used, res.size() - used);
			if (n == -1) {
				goto readBreak;
			}
			used += n;
		  }
		  if (used == res.size()) {
			  res = Arrays::copyOf(res, res.size() * 2);
		  }
			readContinue:;
		}
		readBreak:
		return Arrays::copyOf(res, used);
	  } catch (const IOException &e) {
		throw DomainError(L"failed to read I/O", shared_from_this());
	  }
	}

	std::wstring Scope::NC::repr() {
	  return L"⎕NC";
	}

	std::shared_ptr<Value> Scope::NC::call(std::shared_ptr<Value> w) {
	  std::shared_ptr<Obj> obj = outerInstance->get(w->asString());
	  if (obj == nullptr) {
		  return Num::ZERO;
	  }
	  if (std::dynamic_pointer_cast<Value>(obj) != nullptr) {
		  return Num::NUMS[2];
	  }
	  if (std::dynamic_pointer_cast<Fun>(obj) != nullptr) {
		  return Num::NUMS[3];
	  }
	  if (std::dynamic_pointer_cast<Dop>(obj) != nullptr) {
		  return Num::NUMS[4];
	  }
	  if (std::dynamic_pointer_cast<Mop>(obj) != nullptr) {
		  return Num::NUMS[5];
	  }
	  return Num::NUMS[9];
	}

	std::wstring Scope::Hasher::repr() {
	  return L"⎕HASH";
	}

	std::shared_ptr<Value> Scope::Hasher::call(std::shared_ptr<Value> w) {
	  return Num::of(w->hashCode());
	}

	std::wstring Scope::Stdin::repr() {
	  return L"⎕STDIN";
	}

	std::shared_ptr<Value> Scope::Stdin::call(std::shared_ptr<Value> w) {
	  if (std::dynamic_pointer_cast<Num>(w) != nullptr) {
		int n = w->asInt();
		std::vector<std::shared_ptr<Value>> res(n);
		for (int i = 0; i < n; i++) {
			res.push_back(Main::toAPL(Main::console->nextLine()));
		}
		return std::make_shared<HArr>(res);
	  }
	  if (w->ia == 0) {
		std::vector<std::shared_ptr<Value>> res;
		while (Main::console->hasNext()) {
			res.push_back(Main::toAPL(Main::console->nextLine()));
			Main.console++;
		}
		return std::make_shared<HArr>(res);
	  }
	  throw DomainError(L"⎕STDIN needs either ⍬ or a number as ⍵", shared_from_this());
	}

	Scope::Profiler::Profiler(std::shared_ptr<Scope> sc) : Builtin(sc) {
	}

const std::unordered_map<std::wstring, std::shared_ptr<Pr>> Scope::Profiler::pfRes = std::unordered_map<std::wstring, std::shared_ptr<Pr>>();

	std::shared_ptr<Obj> Scope::Profiler::results() {
	  std::vector<std::shared_ptr<Value>> arr(pfRes.size() * 4 + 4);
	  arr[0] = std::make_shared<ChrArr>(L"expr");
	  arr[1] = std::make_shared<ChrArr>(L"calls");
	  arr[2] = std::make_shared<ChrArr>(L"total ms");
	  arr[3] = std::make_shared<ChrArr>(L"avg ms");
	  const std::vector<int> p = {4};
	  pfRes.forEach([&] (s, pr) {
	  arr[p[0]++] = Main::toAPL(s);
	  arr[p[0]++] = std::make_shared<Num>(pr::am);
	  arr[p[0]++] = std::make_shared<Num>(std::floor(pr::ms * 1e6) / 1e6);
	  arr[p[0]++] = std::make_shared<Num>(std::floor(pr::ms * 1e6 / pr::am) / 1e6);
	  });
	  pfRes.clear();
	  return std::make_shared<HArr>(arr, std::vector<int>{arr.size() >> 2, 4});
	}

	std::wstring Scope::Profiler::repr() {
	  return L"⎕PFX";
	}

	std::shared_ptr<Value> Scope::Profiler::call(std::shared_ptr<Value> w) {
	  return call(w, w);
	}

	std::shared_ptr<Value> Scope::Profiler::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) {
	  std::shared_ptr<Obj> o = callObj(a, w);
	  if (std::dynamic_pointer_cast<Value>(o) != nullptr) {
		  return std::static_pointer_cast<Value>(o);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Was expected to give array, got " + o->humanType(true), shared_from_this()));
	}

	std::shared_ptr<Pr> Scope::Profiler::get(std::shared_ptr<Value> a, std::shared_ptr<Value> w) {
	  std::wstring s = w->asString();
	  std::wstring k = a->asString();
	  std::shared_ptr<Pr> p = pfRes[k];
	  if (p == nullptr) {
		  pfRes.emplace(k, p = std::make_shared<Pr>(Tokenizer::tokenize(s)));
	  }
	  p->am++;
	  return p;
	}

	std::shared_ptr<Obj> Scope::Profiler::callObj(std::shared_ptr<Value> a, std::shared_ptr<Value> w) {
	  std::shared_ptr<Pr> p = get(a, w);
	  std::shared_ptr<BasicLines> t = p->tok;
	  long long sns = System::nanoTime();
	  std::shared_ptr<Obj> res = Main::execLines(t, sc);
	  long long ens = System::nanoTime();
	  p->ms += (ens - sns) / 1000000.0;
	  return res;
	}

	Scope::Profiler::ProfilerOp::ProfilerOp(std::shared_ptr<Scope> sc) : Mop(sc) {
	}

	std::shared_ptr<Pr> Scope::Profiler::ProfilerOp::get(std::shared_ptr<Obj> f) {
	  std::wstring s = (std::static_pointer_cast<Value>(f))->asString();
	  std::shared_ptr<Pr> p = pfRes[s];
	  if (p == nullptr) {
		pfRes.emplace(s, p = std::make_shared<Pr>(Tokenizer::tokenize(s)));
		p->fn = std::static_pointer_cast<Fun>(Main::execLines(p->tok, sc));
	  }
	  p->am++;
	  return p;
	}

	std::shared_ptr<Value> Scope::Profiler::ProfilerOp::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) {
	  std::shared_ptr<Pr> p = get(f);

	  long long sns = System::nanoTime();
	  std::shared_ptr<Value> r = p->fn->call(w);
	  long long ens = System::nanoTime();
	  p->ms += (ens - sns) / 1000000.0;
	  return r;
	}

	std::shared_ptr<Value> Scope::Profiler::ProfilerOp::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) {
	  std::shared_ptr<Pr> p = get(f);

	  long long sns = System::nanoTime();
	  std::shared_ptr<Value> r = p->fn->call(a, w);
	  long long ens = System::nanoTime();
	  p->ms += (ens - sns) / 1000000.0;
	  return r;
	}

	std::wstring Scope::Profiler::ProfilerOp::repr() {
	  return L"⎕PFO";
	}

	Scope::Pr::Pr(std::shared_ptr<BasicLines> tok) : tok(tok) {
	}

	std::shared_ptr<Value> Scope::Big::call(std::shared_ptr<Value> w) {
	  return rec(w);
	}

	std::shared_ptr<Value> Scope::Big::rec(std::shared_ptr<Value> w) {
	  if (std::dynamic_pointer_cast<Num>(w) != nullptr) {
		  return std::make_shared<BigValue>((std::static_pointer_cast<Num>(w))->num);
	  }
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr) {
		  return w;
	  }
	  std::vector<std::shared_ptr<Value>> pa = w->values();
	  std::vector<std::shared_ptr<Value>> va(pa.size());
	  for (int i = 0; i < pa.size(); i++) {
		va[i] = rec(pa[i]);
	  }
	  return std::make_shared<HArr>(va, w->shape);
	}

	std::shared_ptr<Value> Scope::Big::callInv(std::shared_ptr<Value> w) {
	  return recN(w);
	}

	std::shared_ptr<Value> Scope::Big::recN(std::shared_ptr<Value> w) {
	  if (std::dynamic_pointer_cast<BigValue>(w) != nullptr) {
		  return (std::static_pointer_cast<BigValue>(w))->num();
	  }
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr) {
		  return w;
	  }
	  if (std::dynamic_pointer_cast<DoubleArr>(w) != nullptr) {
		  return w;
	  }
	  std::vector<std::shared_ptr<Value>> pa = w->values();
	  std::vector<std::shared_ptr<Value>> va(pa.size());
	  for (int i = 0; i < pa.size(); i++) {
		va[i] = recN(pa[i]);
	  }
	  return Arr::create(va, w->shape);
	}

	std::wstring Scope::Big::repr() {
	  return L"⎕BIG";
	}

	std::shared_ptr<Value> Scope::DR::call(std::shared_ptr<Value> w) {
	  if (std::dynamic_pointer_cast<BitArr>(w) != nullptr) {
		  return Num::of(101);
	  }
	  if (std::dynamic_pointer_cast<Char>(w) != nullptr) {
		  return Num::of(2);
	  }
	  if (std::dynamic_pointer_cast<ChrArr>(w) != nullptr) {
		  return Num::of(102);
	  }
	  if (std::dynamic_pointer_cast<Num>(w) != nullptr) {
		  return Num::of(3);
	  }
	  if (std::dynamic_pointer_cast<DoubleArr>(w) != nullptr) {
		  return Num::of(103);
	  }
	  if (std::dynamic_pointer_cast<APLMap>(w) != nullptr) {
		  return Num::of(4);
	  }
	  if (std::dynamic_pointer_cast<BigValue>(w) != nullptr) {
		  return Num::of(5);
	  }
	  if (std::dynamic_pointer_cast<ArrFun>(w) != nullptr) {
		  return Num::of(8);
	  }
	  if (std::dynamic_pointer_cast<Null>(w) != nullptr) {
		  return Num::of(9);
	  }
	  if (std::dynamic_pointer_cast<Arr>(w) != nullptr) {
		  return Num::of(100);
	  }
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr) {
		  return Num::of(0);
	  }
	  return Num::of(200); // idk ¯\_(ツ)_/¯
	}

	std::shared_ptr<Value> Scope::DR::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) {
	  std::vector<int> is = a->asIntVec();
	  if (is.size() != 2) {
		  throw DomainError(L"⎕DR expected ⍺ to have 2 items", shared_from_this());
	  }
	  int f = is[0];
	  int t = is[1];
	  if ((f == 1 || f == 3 || f == 5) && (t == 1 || t == 3 || t == 5) && (f == 3 ^ t == 3)) {
		// if (w instanceof Num) return new BigValue(Double.doubleToLongBits(w.asDouble()), false);
		// return new Num(Double.longBitsToDouble(((BigValue) w).i.longValue()));
		if (t == 3) {
		  if (f == 1) {
			  return OverBuiltin::on(shared_from_this(), std::make_shared<FunAnonymousInnerClass5>(shared_from_this())}, 1, w);
		  if (f == 5) {
			  return OverBuiltin::on(shared_from_this(), std::make_shared<FunAnonymousInnerClass6>(shared_from_this())}, 0, w);
		  } else {
		  if (t == 1) {
			  return OverBuiltin::on(shared_from_this(), std::make_shared<FunAnonymousInnerClass7>(shared_from_this())}, 0, w);
		  if (t == 5) {
			  return OverBuiltin::on(shared_from_this(), std::make_shared<FunAnonymousInnerClass8>(shared_from_this())}, 0, w);
		  }
		  }
	  throw NYIError(a + L"⎕DR not implemented", shared_from_this());
	}
	Value callInvW(Value a, Value w) {
	  return call(ReverseBuiltin::on(a), w);
	}
	std::wstring repr() {
	  return L"⎕DR";
	}
		  }

		}
	  }
	}
