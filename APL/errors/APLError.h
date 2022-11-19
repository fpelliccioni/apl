#pragma once

#include <APL/tokenizer/Token.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <APL/Sys.h>
#include <string>
#include <vector>
#include <memory>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace APL::errors { class Mg; }

namespace APL::errors
{

	using namespace APL;
	using Token = APL::tokenizer::Token;
	using namespace APL::types;


	class APLError : public RuntimeException, public std::enable_shared_from_this<APLError>
	{
  public:
	  std::shared_ptr<Tokenable> cause;

  protected:
	  APLError(const std::wstring &msg);
	  APLError(const std::wstring &msg, std::shared_ptr<Tokenable> blame);
	  APLError(const std::wstring &msg, std::shared_ptr<Callable> blame, std::shared_ptr<Tokenable> cause);


  public:
	  virtual void print(std::shared_ptr<Sys> s);

	  virtual void println(std::shared_ptr<Sys> s, std::vector<std::shared_ptr<Mg>> &gs);

  public:
	  class Mg : public std::enable_shared_from_this<Mg>
	  {
	public:
		const std::shared_ptr<Token> t;
		const wchar_t c;
		const std::wstring raw;
		int lns = 0;
		int spos = 0, epos = 0; // in the line

		Mg(std::shared_ptr<Token> t, wchar_t c, const std::wstring &raw, int lns, int spos, int epos);

		static void add(std::vector<std::shared_ptr<Mg>> &l, std::shared_ptr<Tokenable> to, wchar_t c);

		virtual bool eqSrc(std::shared_ptr<Mg> g);
	  };
	};
}
