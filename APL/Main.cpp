//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/Main.h>
#include <APL/types/Num.h>
#include <APL/errors/DomainError.h>
#include <APL/Exec.h>
#include <APL/tokenizer/Tokenizer.h>
#include <APL/tokenizer/types/BasicLines.h>
#include <APL/types/Settable.h>
#include <APL/errors/SyntaxError.h>
#include <APL/tokenizer/Token.h>
#include <APL/tokenizer/types/SetTok.h>

namespace APL
{
	using namespace APL::errors;
	using namespace APL::tokenizer;
	using namespace APL::tokenizer::types;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using StandardCharsets = java::nio::charset::StandardCharsets;
const std::wstring Main::CODEPAGE = L"\0\0\0\0\0\0\0\0\0\t\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0 !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~÷×↑↓⌈⌊≠∊⍺⍴⍵⍳∍⋾⎕⍞⌸⌺⍇⍁⍂⌻⌼⍃⍄⍈⍌⍍⍐⍓⍔⍗⍯⍰⍠⌹⊆⊇⍶⍸⍹⍘⍚⍛⍜⍊≤≥⍮ϼ⍷⍉⌽⊖⊙⌾○∘⍟⊗¨⍨⍡⍥⍩⍣⍢⍤⊂⊃∩∪⊥⊤∆∇⍒⍋⍫⍱⍲∨∧⍬⊣⊢⌷⍕⍎←→⍅⍆⍏⍖⌿⍀⍪≡≢⍦⍧⍭‽⍑∞…√ᑈᐵ¯⍝⋄⌶⍙";
bool Main::debug = false;
bool Main::vind = false;
bool Main::noBoxing = false;
bool Main::quotestrings = false;
bool Main::enclosePrimitives = false;
bool Main::colorful = true;
const std::shared_ptr<ChrArr> Main::alphabet = toAPL(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const std::shared_ptr<ChrArr> Main::lowercaseAlphabet = toAPL(L"abcdefghijklmnopqrstuvwxyz");
const std::shared_ptr<ChrArr> Main::digits = toAPL(L"0123456789");
int Main::printlvl = 0;
std::shared_ptr<Scanner> Main::console;
std::shared_ptr<Tokenable> Main::faulty;
std::shared_ptr<APLError> Main::lastError = nullptr;

	void Main::main(std::vector<std::wstring> &args)
	{
	  colorful = System::console() != nullptr && System::getenv()->get(L"TERM") != nullptr;
	  console = std::make_shared<Scanner>(System::in);
	  std::shared_ptr<Sys> sys = StdSys::inst;
	  bool REPL = false;
	  bool silentREPL = false;
	  if (args.size() > 0)
	  {
		try
		{
		  for (int i = 0; i < args.size(); i++)
		  {
			std::wstring p = args[i];
			if (p.length() >= 2 && p[0] == L'-')
			{
			  if (p[1] == L'-')
			  {
//JAVA TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
//				switch (p)
//ORIGINAL LINE: case "--help":
				if (p == L"--help")
				{
					std::wcout << L"Usage: APL [options]" << std::endl;
					std::wcout << L"Options:" << std::endl;
					std::wcout << L"-f file: execute the contents of the file" << std::endl;
					std::wcout << L"-e code: execute the argument as APL" << std::endl;
					std::wcout << L"-p code: execute the argument as APL and print its result" << std::endl;
					std::wcout << L"-i     : execute STDIN as APL" << std::endl;
					std::wcout << L"-r     : start the REPL after everything else" << std::endl;
					std::wcout << L"-s     : start the REPL without \">\" after everything else" << std::endl;
					std::wcout << L"-d     : enable debug mode" << std::endl;
					std::wcout << L"-q     : quote strings in output" << std::endl;
					std::wcout << L"-b     : disable boxing" << std::endl;
					std::wcout << L"-c     : disable colorful printing" << std::endl;
					std::wcout << L"-q     : enable quoting strings" << std::endl;
					std::wcout << L"⎕A←B   : set quad A to B" << std::endl;
					std::wcout << L"-D file: run the file as SBCS" << std::endl;
					std::wcout << L"-E a b : encode the file A in the SBCS, save as B" << std::endl;
					std::wcout << L"If given no arguments, an implicit -r will be added" << std::endl;
					exit(0);
				}
				else
				{
					throw DomainError(StringHelper::wstring_to_string(L"Unknown command-line argument " + p));
				}
			  }
			  else
			  {
				for (auto c : std::vector<wchar_t>(p.substr(1).begin(), p.substr(1).end()))
				{
				  switch (c)
				  {
					case L'f':
					{
					  std::wstring name = args[++i];
					  sys->execFile(Paths->get(name), sys->gsc);
					  break;
					}
					case L'⎕':
					  throw DomainError(L"⎕ settings must be a separate argument");
					case L'e':
					{
					  std::wstring code = args[++i];
					  exec(code, sys->gsc);
					  break;
					}
					case L'p':
					  code = args[++i];
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
					  sys->println(exec(code, sys->gsc)->toString());
					  break;
					case L'i':
					{
					  std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>();
					  while (console->hasNext())
					  {
						s->append(console->nextLine())->append(L'\n');
						  console++;
					  }
					  exec(s->toString(), sys->gsc);
					  break;
					}
					case L'r':
					  REPL = true;
					  break;
					case L's':
					  REPL = true;
					  silentREPL ^= true;
					  break;
					case L'd':
					  debug = true;
					  break;
					case L'q':
					  quotestrings = true;
					  break;
					case L'b':
					  noBoxing = true;
					  break;
					case L'c':
					  colorful = false;
					  break;
					case L'E': {
					  std::wstring origS = readFile(args[++i]);
					  std::vector<signed char> res(origS.length());
					  for (int j = 0; j < origS.length(); j++) {
						wchar_t chr = origS[j];
						int index = (int)CODEPAGE.find(chr);
						if (index == -1) {
							throw DomainError(StringHelper::wstring_to_string(L"error encoding character " + StringHelper::toString(chr) + L" (" + StringHelper::toString(+chr) + L")"));
						}
						res[j] = static_cast<signed char>(index);
					  }
					  std::wstring conv = args[++i];
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (FileOutputStream stream = new FileOutputStream(conv))
					  {
						  FileOutputStream stream = FileOutputStream(conv);
						  try {
							stream.write(res);
						  } catch (const IOException &e) {
							e->printStackTrace();
							throw DomainError(L"couldn't write file");
						  }
					  }
					  break;
					}
					case L'D':
					  try {
						std::vector<signed char> bytes = Files::readAllBytes((std::make_shared<File>(args[++i]))->toPath());
						std::shared_ptr<StringBuilder> res = std::make_shared<StringBuilder>();
						for (auto b : bytes) {
						  res->append(CODEPAGE[b & 0xff]);
						}
						exec(res->toString(), sys->gsc);
					  } catch (const IOException &e) {
						e->printStackTrace();
						throw DomainError(L"couldn't read file");
					  }
					  break;
					default:
					  throw DomainError(StringHelper::wstring_to_string(L"Unknown command-line argument -" + StringHelper::toString(c)));
				  }
				}
			  }
			} else if (p[0] == L'⎕') {
			  int si = (int)p.find(L'←');
			  if (si == -1) {
				  throw DomainError(StringHelper::wstring_to_string(L"argument `" + p + L"` didn't contain a `←`"));
			  }
			  std::wstring qk = p.substr(0, si);
			  std::wstring qv = p.substr(si + 1);
			  sys->gsc->set(qk, exec(qv, sys->gsc));
			} else {
			  throw DomainError(StringHelper::wstring_to_string(L"Unknown command-line argument " + p));
			}
		  }
		} catch (const APLError &e) {
		  e->print(sys);
		  throw e;
		} catch (const std::runtime_error &e) {
		  e.printStackTrace();
		  sys->colorprint(e + L": " + e.what(), 246);
		  throw e;
		}
	  }
	  if (args.empty() || REPL) {
		if (!silentREPL) {
			sys->print(L"> ");
		}
		while (console->hasNext()) {
		  faulty = nullptr;
		  std::wstring cr = console->nextLine();
		  sys->lineCatch(cr);
		  if (!silentREPL) {
			  sys->print(L"> ");
		  }
			console++;
		}
	  }
	}

const std::shared_ptr<StdSys> Main::StdSys::inst = std::make_shared<StdSys>();

	void Main::StdSys::println(const std::wstring &s) {
	  std::wcout << s << std::endl;
	}

	void Main::StdSys::print(const std::wstring &s) {
	  std::wcout << s;
	}

	void Main::StdSys::colorprint(const std::wstring &s, int col) {
	  if (colorful) {
		  println(L"\u001b[38;5;" + std::to_wstring(col) + L"m" + s + L"\u001b[0m");
	  } else {
		  println(s);
	  }
	}

	void Main::StdSys::off(int code) {
	  exit(code);
	}

	std::wstring Main::StdSys::input() {
	  return console->nextLine();
	}

	std::wstring Main::formatAPL(std::vector<int> &ia) {
	  if (ia.empty()) {
		  return L"⍬";
	  }
	  std::shared_ptr<StringBuilder> r = std::make_shared<StringBuilder>(Num::formatInt(ia[0]));
	  for (int i = 1; i < ia.size(); i++) {
		r->append(L" ");
		r->append(Num::formatInt(ia[i]));
	  }
	  return r->toString();
	}

	std::wstring Main::readFile(const std::wstring &path) {
	  return readFile(Paths->get(path));
	}

	std::wstring Main::readFile(std::shared_ptr<Path> path) {
	  try {
		std::vector<signed char> encoded = Files::readAllBytes(path);
		return std::wstring(encoded, StandardCharsets::UTF_8);
	  } catch (const IOException &e) {
		std::wstring msg = L"File " + path + L" not found";
		if (path->startsWith(L"'") && path->endsWith(L"'") || path->startsWith(L"\"") && path->endsWith(L"\"")) {
		  msg += L" (argument shouldn't be surrounded in quotes)";
		}
		std::shared_ptr<DomainError> ne = std::make_shared<DomainError>(msg);
		ne->initCause(e);
		throw ne;
	  }
	}

	std::shared_ptr<Obj> Main::rexec(std::shared_ptr<LineTok> s, std::shared_ptr<Scope> sc) {
	  return (std::make_shared<Exec>(s, sc))->exec();
	}

	std::shared_ptr<Obj> Main::exec(const std::wstring &s, std::shared_ptr<Scope> sc) {
	  std::shared_ptr<BasicLines> t = Tokenizer::tokenize(s);
	  printdbg(sc, std::vector<std::any> {
		  std::vector<std::any> {t}
	  });
	  return execLines(t, sc);
	}

	std::shared_ptr<Obj> Main::exec(std::shared_ptr<LineTok> s, std::shared_ptr<Scope> sc) {
	  std::shared_ptr<Obj> val = (std::make_shared<Exec>(s, sc))->exec();
	  if (std::dynamic_pointer_cast<Settable>(val) != nullptr) {
		  val = (std::static_pointer_cast<Settable>(val))->get();
	  }
	  return val;
	}

	std::shared_ptr<Value> Main::vexec(const std::wstring &s, std::shared_ptr<Scope> sc) {
	  std::shared_ptr<Obj> val = Main::exec(s, sc);
	  if (std::dynamic_pointer_cast<Value>(val) != nullptr) {
		  return std::static_pointer_cast<Value>(val);
	  }
	  throw SyntaxError(StringHelper::wstring_to_string(L"expected array, got " + val->humanType(true)));
	}

	std::shared_ptr<Value> Main::vexec(std::shared_ptr<LineTok> s, std::shared_ptr<Scope> sc) {
	  std::shared_ptr<Obj> val = Main::exec(s, sc);
	  if (std::dynamic_pointer_cast<Value>(val) != nullptr) {
		  return std::static_pointer_cast<Value>(val);
	  }
	  throw SyntaxError(StringHelper::wstring_to_string(L"expected array, got " + val->humanType(true), s));
	}

	void Main::printdbg(std::shared_ptr<Scope> sc, std::vector<std::any> &args) {
	  if (!debug) {
		  return;
	  }
	  std::shared_ptr<StringBuilder> r = std::make_shared<StringBuilder>();
	  if (args->length > 0) {
		  r->append(args[0]);
	  }
	  for (int i = 1; i < args->length; i++) {
		  r->append(L" ")->append(args[i]);
	  }
	  sc->sys->println(r->toString());
	}

	bool Main::isBool(std::shared_ptr<Value> a) {
	  if (!(std::dynamic_pointer_cast<Num>(a) != nullptr)) {
		  return false;
	  }
	  std::shared_ptr<Num> n = std::static_pointer_cast<Num>(a);
	  return n->num == 0 || n->num == 1;
	}

	std::shared_ptr<Obj> Main::execLines(std::shared_ptr<TokArr<std::shared_ptr<LineTok>>> lines, std::shared_ptr<Scope> sc) {
	  std::shared_ptr<Obj> res = nullptr;
	  std::unordered_map<EType, std::shared_ptr<LineTok>> eGuards;
	  try {
		for (auto ln : lines->tokens) {
		  std::vector<std::shared_ptr<Token>> &tokens = ln->tokens;
		  int guardPos = ln->colonPos();
		  int eguardPos = ln->eguardPos();
		  if (guardPos != -1 && eguardPos != -1) {
			  throw SyntaxError(L"both : and :: found in line");
		  }
		  bool endAfter = tokens.size() > 1 && std::dynamic_pointer_cast<SetTok>(tokens[0]) != nullptr;
		  if (endAfter) {
			  tokens = tokens.subList(1, tokens.size());
		  } else if (guardPos != -1) {
			if (guardPos == tokens.size() - 1) {
				throw SyntaxError(L"Guard without success expression");
			}
			if (std::dynamic_pointer_cast<SetTok>(tokens[guardPos + 1]) != nullptr) {
				endAfter = true;
			}
		  } else if (eguardPos != -1) {
			if (eguardPos == tokens.size() - 1) {
				throw SyntaxError(L"Error guard without success expression");
			}
		  }
		  if (guardPos != -1) {
			auto guard = LineTok::inherit(tokens.subList(0, guardPos));
			if (bool_Keyword(vexec(guard, sc))) {
			  auto expr = LineTok::inherit(tokens.subList(guardPos + (endAfter? 2 : 1), tokens.size()));
			  res = exec(expr, sc);
			  if (endAfter) {
				  return res;
			  }
			}
		  } else if (eguardPos != -1) {
			auto guard = LineTok::inherit(tokens.subList(0, eguardPos));
			std::shared_ptr<Value> r = vexec(guard, sc);
			EType t;
			if (r->equals(Num::ZERO)) {
				t = EType::all;
			} else {
				throw DomainError(StringHelper::wstring_to_string(L"guard " + r + L" not supported", guard));
			}
			auto expr = LineTok::inherit(tokens.subList(eguardPos + (endAfter? 2 : 1), tokens.size()));
			eGuards.emplace(t, expr);
		  } else {
			res = exec(endAfter? LineTok::inherit(tokens) : ln, sc);
			if (endAfter) {
				return res;
			}
		  }
		}
		if (std::dynamic_pointer_cast<Settable>(res) != nullptr) {
			return (std::static_pointer_cast<Settable>(res))->get();
		}
	  } catch (const std::runtime_error &e) {
		for (auto entry : eGuards) {
		  EType t = entry->getKey();
		  if (t == EType::all) {
			  return vexec(entry->getValue(), sc);
		  }
		}
		throw e;
	  }
	  return res;
	}

	bool Main::bool_Keyword(double d) {
	  if (d == 1) {
		  return true;
	  }
	  if (d == 0) {
		  return false;
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Expected boolean, got " + std::to_wstring(d)));
	}

	bool Main::bool_Keyword(std::shared_ptr<Obj> v) {
	  if (std::dynamic_pointer_cast<Num>(v) != nullptr) {
		double num = (std::static_pointer_cast<Num>(v))->num;
		if (num == 1) {
			return true;
		}
		if (num == 0) {
			return false;
		}
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Expected boolean, got " + v, v));
	}

	std::shared_ptr<DoubleArr> Main::toAPL(std::vector<int> &arr) {
	  auto *da = std::vector<double>(arr.size());
	  for (int i = 0; i < arr.size(); i++) {
		da[i] = arr[i];
	  }
	  return std::make_shared<DoubleArr>(da);
	}

	std::shared_ptr<DoubleArr> Main::toAPL(std::vector<int> &arr, std::vector<int> &sh) {
	  auto *da = std::vector<double>(arr.size());
	  for (int i = 0; i < arr.size(); i++) {
		da[i] = arr[i];
	  }
	  return std::make_shared<DoubleArr>(da, sh);
	}

	std::shared_ptr<ChrArr> Main::toAPL(const std::wstring &s) {
	  return std::make_shared<ChrArr>(s);
	}

	std::wstring Main::repeat(const std::wstring &s, int l) {
	  std::shared_ptr<StringBuilder> r = std::make_shared<StringBuilder>();
	  for (int i = 0; i < l; i++) {
		  r->append(s);
	  }
	  return r->toString();
	}
}
