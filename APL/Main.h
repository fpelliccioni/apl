#pragma once

#include <APL/types/arrs/ChrArr.h>
#include <APL/types/Tokenable.h>
#include <APL/errors/APLError.h>
#include <APL/Sys.h>
#include <APL/Scope.h>
#include <APL/tokenizer/types/LineTok.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/tokenizer/types/TokArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <any>
#include <utility>
#include <helpers/tangible_exception_helper.h>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL
{

	using namespace APL::errors;
	using namespace APL::tokenizer;
	using namespace APL::tokenizer::types;
	using namespace APL::types;
	using namespace APL::types::arrs;


//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("WeakerAccess") public class Main
	class Main : public std::enable_shared_from_this<Main>
	{
  public:
	  static const std::wstring CODEPAGE;
	  static bool debug;
	  static bool vind; // vector indexing
	  static bool noBoxing;
	  static bool quotestrings;
	  static bool enclosePrimitives;
	  static bool colorful;
	  static const std::shared_ptr<ChrArr> alphabet;
	  static const std::shared_ptr<ChrArr> lowercaseAlphabet;
	  static const std::shared_ptr<ChrArr> digits;
	  static int printlvl;
	  static const long long startingMillis = System::currentTimeMillis();
	  static std::shared_ptr<Scanner> console;
	  static std::shared_ptr<Tokenable> faulty;
	  static std::shared_ptr<APLError> lastError;
	  static void main(std::vector<std::wstring> &args);


  public:
	  class StdSys : public Sys
	  {
	public:
		static const std::shared_ptr<StdSys> inst;
		void println(const std::wstring &s) override;
		void print(const std::wstring &s) override;

		void colorprint(const std::wstring &s, int col) override;

		void off(int code) override;

		std::wstring input() override;

	  protected:
		  std::shared_ptr<StdSys> shared_from_this()
		  {
			  return std::static_pointer_cast<StdSys>(Sys::shared_from_this());
		  }
	  };





  public:
	  static std::wstring formatAPL(std::vector<int> &ia);
	  static std::wstring readFile(const std::wstring &path);
	  static std::wstring readFile(std::shared_ptr<Path> path);

	  static std::shared_ptr<Obj> rexec(std::shared_ptr<LineTok> s, std::shared_ptr<Scope> sc);
	  static std::shared_ptr<Obj> exec(const std::wstring &s, std::shared_ptr<Scope> sc);
	  static std::shared_ptr<Obj> exec(std::shared_ptr<LineTok> s, std::shared_ptr<Scope> sc);
	  static std::shared_ptr<Value> vexec(const std::wstring &s, std::shared_ptr<Scope> sc);
	  static std::shared_ptr<Value> vexec(std::shared_ptr<LineTok> s, std::shared_ptr<Scope> sc);


	  static void printdbg(std::shared_ptr<Scope> sc, std::vector<std::any> &args);

	  static bool isBool(std::shared_ptr<Value> a);

  public:
	  enum class EType
	  {
		all
	  };

	  class ETypeHelper
	  {
	  private:
		  static std::vector<std::pair<EType, std::wstring>> pairs()
		  {
			  return
			  {
				  {EType::all, L"all"}
			  };
		  }

	  public:
		  static std::vector<EType> values()
		  {
			  std::vector<EType> temp;
			  for (auto pair : pairs())
			  {
				  temp.push_back(pair.first);
			  }
			  return temp;
		  }

		  static std::wstring enumName(EType value)
		  {
			  for (auto pair : pairs())
			  {
				  if (pair.first == value)
					  return pair.second;
			  }

			  throw std::runtime_error("Enum not found.");
		  }

		  static int ordinal(EType value)
		  {
			  std::vector<std::pair<EType, std::wstring>> temp = pairs();
			  for (std::size_t i = 0; i < temp.size(); i++)
			  {
				  if (temp[i].first == value)
					  return i;
			  }

			  throw std::runtime_error("Enum not found.");
		  }

		  static EType enumFromString(std::wstring value)
		  {
			  for (auto pair : pairs())
			  {
				  if (pair.second == value)
					  return pair.first;
			  }

			  throw std::runtime_error("Enum not found.");
		  }
	  };



  public:
	  static std::shared_ptr<Obj> execLines(std::shared_ptr<TokArr<std::shared_ptr<LineTok>>> lines, std::shared_ptr<Scope> sc);
	  static bool bool_Keyword(double d);

	  static bool bool_Keyword(std::shared_ptr<Obj> v);

	  static std::shared_ptr<DoubleArr> toAPL(std::vector<int> &arr);

	  static std::shared_ptr<DoubleArr> toAPL(std::vector<int> &arr, std::vector<int> &sh);

	  static std::shared_ptr<ChrArr> toAPL(const std::wstring &s);


	  static std::wstring repeat(const std::wstring &s, int l);
	};
}
