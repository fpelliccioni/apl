#include <APL/VarArr.h>
#include <APL/Main.h>
#include <APL/Value.h>
#include <APL/arrs/EmptyArr.h>
#include <APL/Num.h>
#include <APL/arrs/BitArr.h>
#include <APL/arrs/DoubleArr.h>
#include <APL/Char.h>
#include <APL/arrs/ChrArr.h>

namespace APL::types::functions
{
	using namespace APL;
	using LengthError = APL::errors::LengthError;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using SetBuiltin = APL::types::functions::builtins::SetBuiltin;

	VarArr::VarArr(std::vector<std::shared_ptr<Obj>> &arr) : Settable(nullptr), ia(arr.size())
	{
	  if (arr.size() > 0)
	  {
		  this->token = arr[0]->token;
	  }
	  std::reverse(arr.begin(), arr.end());
	  this->arr = arr;
	}

	std::shared_ptr<Arr> VarArr::get()
	{
	  if (this->token != nullptr)
	  {
		  Main::faulty = shared_from_this();
	  }
	  std::vector<std::shared_ptr<Value>> res(arr.size());
	  for (int i = 0; i < ia; i++)
	  {
		std::shared_ptr<Obj> c = arr[i];
		res[i] = std::dynamic_pointer_cast<VarArr>(c) != nullptr? (std::static_pointer_cast<VarArr>(c))->get() : std::static_pointer_cast<Value>(std::dynamic_pointer_cast<Value>(c) != nullptr? c : (std::static_pointer_cast<Settable>(c))->get());
	  }
	  return Arr::create(res);
	}

	APL::Type VarArr::type()
	{
	  return Type::array;
	}

	void VarArr::set(std::shared_ptr<Obj> v, std::shared_ptr<Callable> blame)
	{
	  set(v, false);
	}

	std::wstring VarArr::toString()
	{
	  if (Main::debug)
	  {
		  return L"vararr:" + arr;
	  }
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  return get()->toString();
	}

	std::shared_ptr<Obj> VarArr::of(std::vector<std::shared_ptr<Obj>> &vs)
	{
	  int sz = vs.size();
	  if (sz == 0)
	  {
		  return EmptyArr::SHAPE0Q;
	  }
	  std::shared_ptr<Obj> fst = vs[0];
	  if (std::dynamic_pointer_cast<Num>(fst) != nullptr)
	  {
		if ((std::static_pointer_cast<Num>(fst))->num == 0 || (std::static_pointer_cast<Num>(fst))->num == 1)
		{
		  std::shared_ptr<BitArr::BA> bc = std::make_shared<BitArr::BA>(sz);
		  int i = sz - 1;
		  while (i >= 0)
		  {
			std::shared_ptr<Obj> c = vs[i];
			if (std::dynamic_pointer_cast<Num>(c) != nullptr)
			{
			  double n = (std::static_pointer_cast<Num>(c))->num;
			  if (Double::doubleToRawLongBits(n) == 0 || n == 1)
			  { // don't convert negative zero!
				bc->add(n == 1);
			  }
			  else
			  {
				  bc = nullptr;
				  break;
			  }
			}
			else
			{
				bc = nullptr;
				break;
			}
			i--;
		  }
		  if (bc != nullptr)
		  {
			  return bc->finish();
		  }
		}
		std::vector<double> a(sz);
		int i = 0;
		while (i < a.size())
		{
		  std::shared_ptr<Obj> c = vs[i];
		  if (std::dynamic_pointer_cast<Num>(c) != nullptr)
		  {
			a[a.size() - i - 1] = (std::static_pointer_cast<Num>(c))->num;
			i++;
		  }
		  else
		  {
			a = std::vector<double>();
			break;
		  }
		}
		if (!a.empty())
		{
			return std::make_shared<DoubleArr>(a);
		}
	  }
	  else if (std::dynamic_pointer_cast<Char>(fst) != nullptr)
	  {
		std::wstring s = L"";
		int i = sz - 1;
		while (i >= 0)
		{
		  std::shared_ptr<Obj> c = vs[i];
		  if (std::dynamic_pointer_cast<Char>(c) != nullptr)
		  {
			s += (std::static_pointer_cast<Char>(c))->chr;
			i--;
		  }
		  else
		  {
			s = L"";
			break;
		  }
		}
		if (s != L"")
		{
			return std::make_shared<ChrArr>(s);
		}
	  }
	  return std::make_shared<VarArr>(vs);
	}

	void VarArr::set(std::shared_ptr<Obj> w, bool update)
	{
	  std::shared_ptr<Value> ow = std::static_pointer_cast<Value>(w);
	  if (ow->rank == 0)
	  {
		ow = ow->first();
		for (int i = 0; i < ia; i++)
		{
			SetBuiltin::inst->callObj(arr[i], ow, update);
		}
	  }
	  else
	  {
		if (ow->rank != 1)
		{
			throw LengthError(L"← scatter rank ≠1", ow);
		}
		if (ow->ia != ia)
		{
			throw LengthError(L"← scatter argument lengths not equal", ow);
		}
		for (int i = 0; i < ia; i++)
		{
			SetBuiltin::inst->callObj(arr[i], ow[i], update);
		}
	  }
	}
}
