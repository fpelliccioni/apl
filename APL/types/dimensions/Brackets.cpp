#include <APL/types/dimensions/Brackets.h>
#include <APL/tokenizer/types/LineTok.h>
#include <APL/Main.h>

namespace APL::types::dimensions
{
	using namespace APL;
	using namespace APL::tokenizer::types;
	using namespace APL::types;
	using UpArrowBuiltin = APL::types::functions::builtins::fns::UpArrowBuiltin;

	Brackets::Brackets(std::shared_ptr<Value> val) : Callable(nullptr), val(val)
	{
	}

	std::optional<int> Brackets::toInt()
	{
	  return val->empty()? std::nullopt : val->asInt();
	}

	std::vector<int> Brackets::toInts()
	{
	  return val->empty()? std::vector<int>() : val->asIntVec();
	}

	APL::Type Brackets::type()
	{
	  return Type::dim;
	}

	std::wstring Brackets::toString()
	{
	  return L"[" + val + L"]";
	}

	std::shared_ptr<Obj> Brackets::of(std::shared_ptr<BracketTok> t, std::shared_ptr<Scope> sc)
	{
	  if (t->array)
	  {
		std::vector<std::shared_ptr<Value>> lns(t->tokens.size());
		for (int i = 0; i < t->tokens.size(); i++)
		{
		  std::shared_ptr<LineTok> tk = t->tokens[i];
		  lns[i] = Main::vexec(tk, sc);
		}
		return UpArrowBuiltin::merge(lns, std::vector<int>{lns.size()}, t);
	  }
	  else
	  {
		if (t->tokens.empty())
		{
			return std::make_shared<Brackets>(nullptr);
		}
		assert(t->tokens.size() == 1); // t.array is true if size>1
		std::shared_ptr<Value> res = Main::vexec(t->tokens[0], sc);
		return std::make_shared<Brackets>(res);
	  }
	}
}
