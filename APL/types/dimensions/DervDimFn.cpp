#include <APL/types/dimensions/DervDimFn.h>
#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/dimensions/DimDFn.h>
#include <APL/errors/SyntaxError.h>
#include <APL/DimMFn.h>

namespace APL::types::dimensions
{
	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;

	std::wstring DervDimFn::repr()
	{
	  return f->repr() + L"[" + Main::formatAPL(raw) + L"]";
	}

	DervDimFn::DervDimFn(std::shared_ptr<Fun> f, std::vector<int> &raw, std::shared_ptr<Scope> sc) : Fun(sc), IO(sc->IO), f(f), raw(raw)
	{
	  if (raw.empty())
	  {
		  dims_Conflict = std::vector<int>{0};
	  }
	  else
	  {
		dims_Conflict = std::vector<int>(raw.size());
		for (int i = 0; i < raw.size(); i++)
		{
		  int c = raw[i];
		  if (c == 0 && IO == 1)
		  {
//JAVA TO C++ CONVERTER TODO TASK: You cannot use 'shared_from_this' in a constructor:
			  throw DomainError(L"bracket axis cannot contain 0 with ⎕IO←1", shared_from_this());
		  }
		  dims_Conflict[i] = c < 0? c : c - IO;
		}
	  }
	  this->token = f->token;
	}

	std::vector<int> DervDimFn::dims(int rank)
	{
	  std::vector<int> res(dims_Conflict.size());
	  std::vector<bool> used(rank);

	  for (int i = 0; i < dims_Conflict.size(); i++)
	  {
		int c = dims_Conflict[i];
		int ax = c < 0? c + rank : c;
		if (used[ax])
		{
			throw DomainError(StringHelper::wstring_to_string(L"function axis specified axis " + std::to_wstring(ax + IO) + L" twice", shared_from_this()));
		}
		else
		{
			used[ax] = true;
		}
		res[i] = ax;
	  }
	  return res;
	}

	std::shared_ptr<Value> DervDimFn::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (!(std::dynamic_pointer_cast<DimDFn>(f) != nullptr))
	  {
		  throw SyntaxError(StringHelper::wstring_to_string(L"Attempt to dyadically call " + shared_from_this() + L", which doesn't support dimension specification", shared_from_this()));
	  }
	  return (std::static_pointer_cast<DimDFn>(f))->call(a, w, shared_from_this());
	}

	std::shared_ptr<Value> DervDimFn::call(std::shared_ptr<Value> w)
	{
	  if (!(std::dynamic_pointer_cast<DimMFn>(f) != nullptr))
	  {
		  throw SyntaxError(StringHelper::wstring_to_string(L"Attempt to monadically call " + shared_from_this() + L", which doesn't support dimension specification", shared_from_this()));
	  }
	  if (dims_Conflict.size() != 1)
	  {
		  throw DomainError(StringHelper::wstring_to_string(repr() + L" expected one dimension specifier", shared_from_this()));
	  }
	  return (std::static_pointer_cast<DimMFn>(f))->call(w, dims_Conflict[0]);
	}

	int DervDimFn::singleDim(int rank)
	{
	  if (dims_Conflict.size() != 1)
	  {
		  throw DomainError(f + L" expected only one axis specifier", f);
	  }
	  int c = dims_Conflict[0];
	  if (c < 0)
	  {
		  c += rank;
	  }
	  return c;
	}

	int DervDimFn::singleDim()
	{
	  if (dims_Conflict.size() != 1)
	  {
		  throw DomainError(f + L" expected only one axis specifier", f);
	  }
	  return dims_Conflict[0];
	}

	std::wstring DervDimFn::format()
	{
	  return Main::formatAPL(raw);
	}
}
