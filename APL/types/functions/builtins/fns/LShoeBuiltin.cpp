#include <APL/LShoeBuiltin.h>
#include <APL/Primitive.h>
#include <APL/arrs/Rank0Arr.h>
#include <APL/errors/DomainError.h>
#include <APL/errors/LengthError.h>
#include <APL/arrs/DoubleArr.h>
#include <APL/arrs/EmptyArr.h>
#include <APL/Arr.h>

namespace APL::types::functions::builtins::fns
{
	using Main = APL::Main;
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using ArrayList = java::util::ArrayList;

	std::wstring LShoeBuiltin::repr()
	{
	  return L"⊂";
	}

	std::shared_ptr<Value> LShoeBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (!Main::enclosePrimitives && std::dynamic_pointer_cast<Primitive>(w) != nullptr)
	  {
		  return w;
	  }
	  return std::make_shared<Rank0Arr>(w);
	}

	std::shared_ptr<Value> LShoeBuiltin::on(std::shared_ptr<Value> w)
	{
	  return !Main::enclosePrimitives && std::dynamic_pointer_cast<Primitive>(w) != nullptr? w : std::make_shared<Rank0Arr>(w);
	}

	std::shared_ptr<Value> LShoeBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (w->rank != 1)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⊂: ⍵ should be of rank 1 (" + Main::formatAPL(w->shape) + L" ≡ ⍴⍵)", shared_from_this()));
	  }
	  if (a->rank != 1)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⊂: ⍺ should be of rank 1 (" + Main::formatAPL(a->shape) + L" ≡ ⍴⍺)", shared_from_this()));
	  }
	  if (a->ia + 1 != w->ia)
	  {
		  throw LengthError(StringHelper::wstring_to_string(L"⊂: (1+≢⍺) ≡ ≢⍵ is required (" + Main::formatAPL(a->shape) + L" ≡ ⍴⍺; " + Main::formatAPL(w->shape) + L" ≡ ⍴⍵)", shared_from_this()));
	  }
	  std::vector<int> aa = a->asIntVec();
	  std::vector<std::shared_ptr<Value>> parts;

	  if (w->quickDoubleArr())
	  {
		std::vector<double> vals = w->asDoubleArr();
		std::vector<double> cpart;
		for (int i = 0; i < aa.size(); i++)
		{
		  int am = aa[i];
		  cpart.push_back(vals[i]);
		  if (am > 0)
		  {
			parts.push_back(std::make_shared<DoubleArr>(cpart));
			for (int j = 0; j < am - 1; j++)
			{
				parts.push_back(EmptyArr::SHAPE0N);
			}
			cpart.clear();
		  }
		}
		cpart.push_back(vals[vals.size() - 1]);
		parts.push_back(std::make_shared<DoubleArr>(cpart));
	  }
	  else
	  {
		std::vector<std::shared_ptr<Value>> vals = w->values();
		std::vector<std::shared_ptr<Value>> cpart;
		for (int i = 0; i < aa.size(); i++)
		{
		  int am = aa[i];
		  cpart.push_back(vals[i]);
		  if (am > 0)
		  {
			parts.push_back(Arr::create(cpart));
			for (int j = 0; j < am - 1; j++)
			{
				parts.push_back(std::make_shared<EmptyArr>(EmptyArr::SHAPE0, w->safePrototype()));
			}
			cpart.clear();
		  }
		}
		cpart.push_back(vals[vals.size() - 1]);
		parts.push_back(Arr::create(cpart));
	  }
	  return Arr::create(parts);
	}
}
