#include <APL/SquadBuiltin.h>
#include <APL/types/Arr.h>
#include <APL/types/APLMap.h>
#include <APL/errors/DomainError.h>
#include <APL/Main.h>
#include <APL/errors/RankError.h>
#include <APL/errors/LengthError.h>

namespace APL::types::functions::builtins::fns
{
	// using namespace APL;
	// using namespace APL::errors;
	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;
	using Arrays = java::util::Arrays;

	std::string SquadBuiltin::repr()
	{
	  return L"⌷";
	}

	SquadBuiltin::SquadBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
	{
	}

	std::shared_ptr<APL::types::Value> SquadBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  if (std::dynamic_pointer_cast<Arr>(w) != nullptr)
	  {
		  return w;
	  }
	  if (std::dynamic_pointer_cast<APLMap>(w) != nullptr)
	  {
		  return (std::static_pointer_cast<APLMap>(w))->kvPair();
	  }
	  throw DomainError(L"⍵ not array nor map", shared_from_this(), w);
	}

	std::shared_ptr<APL::types::Value> SquadBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::vector<int> p = a->asIntVec();
	  int al = p.size();
	  int wl = w->shape.size();
	  if (al > wl)
	  {
		  throw RankError(StringHelper::wstring_to_string(L"⌷: expected (≢⍺) ≤ ≢⍴⍵ (" + std::to_wstring(al) + L" = ≢⍺; " + Main::formatAPL(w->shape) + L" ≡ ⍴⍵)", shared_from_this(), a));
	  }
	  int sz = 1;
	  for (int i = al; i < wl; i++)
	  {
		  sz *= w->shape[i];
	  }
	  int off = 0;
	  for (int i = 0; i < al; i++)
	  {
		int d = p[i] - sc->IO;
		off += d;
		if (d < 0 || d >= w->shape[i])
		{
			throw LengthError(L"⌷: index out-of-bounds", shared_from_this(), a);
		}
		off *= i >= al - 1? sz : w->shape[i + 1];
	  }
	  return w->cut(off, sz, std::vector<int>(w->shape.cbegin() + al, w->shape.cbegin() + wl));
	}
}
