#include <APL/Sys.h>
#include <APL/Main.h>
#include <APL/types/Value.h>
#include <APL/types/Arr.h>
#include <APL/errors/APLError.h>
#include <APL/types/Callable.h>
#include <APL/errors/DomainError.h>
#include <APL/errors/SyntaxError.h>
#include <APL/errors/ImplementationError.h>

namespace APL
{
	using namespace APL::errors;
	using Tokenizer = APL::tokenizer::Tokenizer;
	using namespace APL::types;
	using HArr = APL::types::arrs::HArr;

	Sys::Sys()
	{
//JAVA TO C++ CONVERTER TODO TASK: You cannot use 'shared_from_this' in a constructor:
	  gsc = csc = std::make_shared<Scope>(shared_from_this());
	  std::shared_ptr<Path> p = Paths->get(L".").toAbsolutePath().normalize();
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  cd = p->toString();
	}

	void Sys::ucmd(const std::wstring &cr)
	{
	  std::vector<std::wstring> parts = cr.split(L" ");
	  std::wstring t = StringHelper::toUpper(parts[0]);
	  std::wstring rest = parts.size() == 1? L"" : cr.substr(t.length() + 1);
//JAVA TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
//	  switch (t)
//ORIGINAL LINE: case "OFF":
	  if (t == L"OFF" || t == L"EXIT" || t == L"STOP")
	  {
		  if (rest.length() == 0)
		  {
			  off(0);
		  }
		  else
		  {
			  off(Main::vexec(rest, csc)->asInt());
		  }
	  }
//ORIGINAL LINE: case "EX":
	  else if (t == L"EX")
	  {
		  std::wstring full = cr.substr((int)cr.find(L" ") + 1);
		  execFile(path(cd, full), gsc);
	  }
//ORIGINAL LINE: case "DEBUG":
	  else if (t == L"DEBUG")
	  {
		  Main::debug = !Main::debug;
	  }
//ORIGINAL LINE: case "QUOTE":
	  else if (t == L"QUOTE")
	  {
		  Main::quotestrings = !Main::quotestrings;
	  }
//ORIGINAL LINE: case "LN":
	  else if (t == L"LN")
	  {
		  if (rest.length() == 0)
		  {
			  Main::noBoxing ^= true;
		  }
		  else
		  {
			  println(Main::vexec(rest, csc)->oneliner());
		  }
	  }
//ORIGINAL LINE: case "TOKENIZE" :
	  else if (t == L"TOKENIZE")
	  {
			println(Tokenizer::tokenize(rest)->toTree(L""));
	  }
//ORIGINAL LINE: case "TOKENIZEREPR":
	  else if (t == L"TOKENIZEREPR")
	  {
			println(Tokenizer::tokenize(rest)->toRepr());
	  }
//ORIGINAL LINE: case "CLASS" :
	  else if (t == L"CLASS")
	  {
			std::shared_ptr<Value> r = Main::vexec(rest, csc);
			println(r->getClass().getCanonicalName());
	  }
//ORIGINAL LINE: case "UOPT" :
	  else if (t == L"UOPT")
	  {
			std::shared_ptr<Arr> e = std::static_pointer_cast<Arr>(csc->get(rest));
			csc->set(rest, std::make_shared<HArr>(e->values(), e->shape));
	  }
//ORIGINAL LINE: case "ATYPE" :
	  else if (t == L"ATYPE")
	  {
			println(Main::exec(rest, csc)->humanType(false));
	  }
//ORIGINAL LINE: case "STACK":
	  else if (t == L"STACK")
	  {
		  if (Main::lastError != nullptr)
		  {
			std::shared_ptr<ByteArrayOutputStream> os = std::make_shared<ByteArrayOutputStream>();
			Main::lastError->printStackTrace(std::make_shared<PrintStream>(os));
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
			println(os->toString());
		  }
		  else
		  {
			  println(L"no stack to view");
		  }
	  }
//ORIGINAL LINE: case "CS":
	  else if (t == L"CS")
	  {
		  if (rest.length() == 0)
		  {
			  csc = gsc;
		  }
		  else
		  {
			std::shared_ptr<Obj> o = Main::exec(rest, csc);
			std::shared_ptr<Scope> nsc = nullptr;
			if (std::dynamic_pointer_cast<Callable>(o) != nullptr)
			{
				nsc = (std::static_pointer_cast<Callable>(o))->sc;
			}
			if (nsc == nullptr)
			{
				throw DomainError(L"argument to )cs wasn't scoped");
			}
			csc = nsc;
		  }
	  }
	  else
	  {
		  throw SyntaxError(L"Undefined user command");
	  }
	}

	std::shared_ptr<Path> Sys::path(const std::wstring &path, const std::wstring &s)
	{
	  if (path == L"")
	  {
		std::shared_ptr<Path> p = Paths->get(s);
		if (!p->isAbsolute())
		{
			throw DomainError(L"Expected code outside files to only use absolute paths");
		}
		return p->normalize();
	  }
	  return Paths->get(path).resolve(s).toAbsolutePath().normalize();
	}

	std::vector<std::wstring> Sys::split(std::shared_ptr<Path> p)
	{
	  p = p->toAbsolutePath().normalize();
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  return std::vector<std::wstring>{p->getParent()->toString() + L"/", p->getFileName()->toString()};
	}

	std::shared_ptr<Obj> Sys::execFile(std::shared_ptr<Path> path, std::shared_ptr<Scope> sc)
	{
	  std::wstring code = Main::readFile(path);
	  return Main::exec(code, sc);
	}

	void Sys::line(const std::wstring &s)
	{
	  if (StringHelper::startsWith(s, L")"))
	  {
		ucmd(s.substr(1));
	  }
	  else
	  {
		std::shared_ptr<Obj> res = Main::exec(s, csc);
		if (res != nullptr)
		{
			println(res);
		}
	  }
	}

	void Sys::lineCatch(const std::wstring &s)
	{
	  try
	  {
		line(s);
	  }
	  catch (const std::runtime_error &t)
	  {
		  report(t);
	  }
	}

	void Sys::report(std::runtime_error t)
	{
	  Main::lastError = std::dynamic_pointer_cast<APLError>(t) != nullptr? std::static_pointer_cast<APLError>(t) : std::make_shared<ImplementationError>(t);
	  Main::lastError->print(shared_from_this());
	}

	void Sys::colorprint(const std::wstring &s, int col)
	{
	  println(s);
	}

	void Sys::println(std::shared_ptr<Obj> v)
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  println(v->toString());
	}
}
