#pragma once

#include <APL/errors/SyntaxError.h>
#include <APL/types/BigValue.h>
#include <APL/Token.h>
#include <APL/types/LineTok.h>
#include <APL/types/BasicLines.h>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <optional>
#include <helpers/tangible_exception_helper.h>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL::tokenizer
{

	using namespace APL::tokenizer::types;

	using ArrayList = java::util::ArrayList;

	class Tokenizer : public std::enable_shared_from_this<Tokenizer>
	{
  private:
	  static const std::vector<wchar_t> validNames;
	  static const std::wstring ops; // stolen from https://bitbucket.org/zacharyjtaylor/rad/src/master/RAD_document.txt?fileviewer=file-view-default
	  static bool validNameStart(wchar_t c);
  public:
	  static bool validNameMid(wchar_t c);
  public:
	  class Line : public std::enable_shared_from_this<Line>
	  {
	public:
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: final java.util.ArrayList<Token> ts;
		std::vector<std::shared_ptr<Token>> ts;
		const std::wstring line;
		const int pos;
		std::optional<int> annoyingBacktickPos;

		Line(const std::wstring &line, int pos, std::vector<std::shared_ptr<Token>> &ts);

		Line(const std::wstring &line, int pos);

		virtual int size();

		virtual void add(std::shared_ptr<Token> r);

		virtual std::shared_ptr<LineTok> tok();
	  };
  public:
	  class Block : public std::enable_shared_from_this<Block>
	  { // temp storage of multiple lines
	public:
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: final java.util.ArrayList<Line> a;
		std::vector<std::shared_ptr<Line>> a;
		const wchar_t b;
		bool hasDmd = false;
	private:
		const int pos;

	public:
		Block(std::vector<std::shared_ptr<Line>> &a, wchar_t b, int pos);
		virtual std::wstring toString();
	  };

  public:
	  static std::shared_ptr<BasicLines> tokenize(const std::wstring &raw);

	  static std::shared_ptr<BasicLines> tokenize(const std::wstring &raw, bool pointless);
	};
}
