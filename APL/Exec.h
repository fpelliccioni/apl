#pragma once

#include <APL/tokenizer/Token.h>
#include <APL/types/functions/builtins/AbstractSet.h>
#include <APL/types/functions/userDefined/UserDefined.h>
#include <APL/Scope.h>
#include <APL/tokenizer/types/LineTok.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/Fun.h>
#include <APL/types/functions/Dop.h>
#include <APL/types/Settable.h>
#include <APL/types/functions/Mop.h>
#include <string>
#include <vector>
#include <stack>
#include <any>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace APL { class Node; }

namespace APL
{

	using namespace APL::errors;
	using Token = APL::tokenizer::Token;
	using namespace APL::tokenizer::types;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::dimensions;
	using namespace APL::types::functions;
	using namespace APL::types::functions::builtins;
	using namespace APL::types::functions::builtins::dops;
	using namespace APL::types::functions::builtins::fns;
	using namespace APL::types::functions::builtins::mops;
	using namespace APL::types::functions::trains;



	class Exec : public std::enable_shared_from_this<Exec>
	{
  private:
	  const std::shared_ptr<Scope> sc;
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final List<APL.tokenizer.Token> tokens;
	  std::vector<std::shared_ptr<Token>> tokens;
	  const std::shared_ptr<LineTok> allToken;

  public:
	  Exec(std::shared_ptr<LineTok> ln, std::shared_ptr<Scope> sc);



  private:
	  void printlvl(std::vector<std::any> &args);
	  std::stack<std::shared_ptr<Token>> left;
  public:
	  virtual std::shared_ptr<Obj> exec();
  private:
	  void update(bool end);

	  std::shared_ptr<Value> lastVal();

	  std::shared_ptr<Fun> lastFun();

	  std::shared_ptr<Value> firstVal();
	  std::shared_ptr<Dop> firstDop();

	  std::shared_ptr<Obj> lastObj();
	  std::shared_ptr<Obj> firstObj();
	  std::shared_ptr<Settable> firstVar();
	  std::shared_ptr<Mop> firstMop();
	  void addFirst(std::shared_ptr<Obj> o);




	  int llSize = 0;
	  std::shared_ptr<Obj> popS();
	  std::shared_ptr<Obj> popE();
	  std::shared_ptr<Obj> popB();
	  void addS(std::shared_ptr<Obj> o);
	  void addE(std::shared_ptr<Obj> o);
	  void addB(std::shared_ptr<Obj> o);
	  std::shared_ptr<Obj> pollS();
	  std::shared_ptr<Obj> pollL();
	  std::shared_ptr<Node> FN, LN;
	  void reset();
  private:
	  class Node : public std::enable_shared_from_this<Node>
	  {
	public:
		std::shared_ptr<Node> l, r;
		wchar_t type = L'\0';
		std::shared_ptr<Obj> val;
		Node();
		Node(std::shared_ptr<Obj> val, std::shared_ptr<Node> l, std::shared_ptr<Node> r);
		virtual std::shared_ptr<Obj> remove();
		virtual std::wstring toString();
	  };
  private:
	  std::wstring llToString();




	  bool is(std::vector<std::wstring> &pts, bool everythingDone, bool fromStart);
	  std::shared_ptr<Node> barNode;
	  bool is(const std::wstring &pt, bool everythingDone, bool fromStart);
	  bool is(const std::wstring &pt, bool everythingDone, bool fromStart, int am);

	  std::shared_ptr<Obj> valueOf(std::shared_ptr<Token> t);

	  std::shared_ptr<Obj> valueOfRaw(std::shared_ptr<Token> t);
	};
}
