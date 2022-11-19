#include <APL/FormatBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using Main = APL::Main;
	using Value = APL::types::Value;
	using ChrArr = APL::types::arrs::ChrArr;
	using Builtin = APL::types::functions::Builtin;

	std::wstring FormatBuiltin::repr()
	{
	  return L"⍕";
	}

	std::shared_ptr<Value> FormatBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (w->rank == 1)
	  {
		w = w->squeeze();
		if (std::dynamic_pointer_cast<ChrArr>(w) != nullptr)
		{
			return Main::toAPL(w->asString());
		}
	  }
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  return Main::toAPL(w->toString());
	}
}
