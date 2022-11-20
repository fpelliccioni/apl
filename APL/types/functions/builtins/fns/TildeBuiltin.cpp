#include <APL/TildeBuiltin.h>
#include <APL/types/Arr.h>
#include <APL/types/Num.h>
#include <APL/types/arrs/HArr.h>

namespace APL::types::functions::builtins::fns
{
	using Main = APL::Main;
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	std::wstring TildeBuiltin::repr()
	{
	  return L"~";
	}

	std::shared_ptr<Value> TildeBuiltin::call(std::shared_ptr<Value> w)
	{
	  return rec(w);
	}

	std::shared_ptr<Value> TildeBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return rec(w);
	}

	std::shared_ptr<Value> TildeBuiltin::rec(std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Arr>(w) != nullptr)
	  {
		if (std::dynamic_pointer_cast<BitArr>(w) != nullptr)
		{
		  std::shared_ptr<BitArr> wb = std::static_pointer_cast<BitArr>(w);
		  std::vector<long long> res(wb->llen());
		  for (int i = 0; i < res.size(); i++)
		  {
			  res[i] = ~wb->arr[i];
		  }
		  return std::make_shared<BitArr>(res, w->shape);
		}

		if (w->quickDoubleArr())
		{
		  // for (int i = 0; i < w.length; i++) if (w[i] == 0) res[i>>6]|= 1L << (i&63);
		  std::shared_ptr<BitArr::BA> a = std::make_shared<BitArr::BA>(w->shape);
		  for (auto v : w->asDoubleArr())
		  {
			  a->add(v == 0);
		  }
		  return a->finish();
		}

		std::shared_ptr<Arr> o = std::static_pointer_cast<Arr>(w);
		if (o->ia > 0 && std::dynamic_pointer_cast<Num>(o[0]) != nullptr)
		{
		  std::shared_ptr<BitArr::BA> a = std::make_shared<BitArr::BA>(w->ia); // it's probably worth going all-in on creating a bitarr
		  for (int i = 0; i < o->ia; i++)
		  {
			std::shared_ptr<Value> v = o[i];
			if (std::dynamic_pointer_cast<Num>(v) != nullptr)
			{
				a->add(!Main::bool_Keyword(v));
			}
			else
			{
			  a = nullptr;
			  break;
			}
		  }
		  if (a != nullptr)
		  {
			  return a->finish();
		  }
		  // could make it reuse the progress made, but ¯\_(ツ)_/¯
		}
		std::vector<std::shared_ptr<Value>> arr(o->ia);
		for (int i = 0; i < o->ia; i++)
		{
		  arr[i] = rec(o[i]);
		}
		return std::make_shared<HArr>(arr, o->shape);
	  }
	  else if (std::dynamic_pointer_cast<Num>(w) != nullptr)
	  {
		  return Main::bool_Keyword(w)? Num::ZERO : Num::ONE;
	  }
	  else
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"Expected boolean, got " + w->humanType(false), shared_from_this(), w));
	  }
	}

	std::shared_ptr<BitArr> TildeBuiltin::call(std::shared_ptr<BitArr> w)
	{
	  std::shared_ptr<BitArr::BC> bc = BitArr::create(w->shape);
	  for (int i = 0; i < bc->arr.size(); i++)
	  {
		bc->arr[i] = ~w->arr[i];
	  }
	  return bc->finish();
	}

	std::shared_ptr<Value> TildeBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  int ia = 0;
	  std::vector<bool> leave(a->ia);
	  for (int i = 0; i < a->ia; i++)
	  {
		std::shared_ptr<Value> v = a[i];
		for (auto c : w)
		{
		  if (v->equals(c))
		  {
			  goto aContinue;
		  }
		}
		leave[i] = true;
		ia++;
		  aContinue:;
	  }
	  aBreak:
	  std::vector<std::shared_ptr<Value>> res(ia);
	  int pos = 0;
	  for (int i = 0; i < leave.size(); i++)
	  {
		if (leave[i])
		{
		  res[pos++] = a[i];
		}
	  }
	  return Arr::create(res);
	}
}
