#include <APL/FormatBuiltin.h>

namespace APL::types::functions::builtins::fns {

// using Main = APL::Main;
// using Value = APL::types::Value;
// using ChrArr = APL::types::arrs::ChrArr;
// using Builtin = APL::types::functions::Builtin;

std::string FormatBuiltin::repr()
{
	return L"⍕";
}

std::shared_ptr<APL::types::Value> FormatBuiltin::call(std::shared_ptr<APL::types::Value> w)
{
	if (w->rank == 1)
	{
	w = w->squeeze();
	if (std::dynamic_pointer_cast<APL::types::arrs::ChrArr>(w) != nullptr)
	{
		return Main::toAPL(w->asString());
	}
	}
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	return Main::toAPL(w->toString());
}

}
