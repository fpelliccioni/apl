#include <APL/GradeDownBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using Scope = APL::Scope;
	using Value = APL::types::Value;
	using DoubleArr = APL::types::arrs::DoubleArr;
	using Builtin = APL::types::functions::Builtin;

	std::wstring GradeDownBuiltin::repr()
	{
	  return L"⍒";
	}

	GradeDownBuiltin::GradeDownBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
	{
	}

	std::shared_ptr<Value> GradeDownBuiltin::call(std::shared_ptr<Value> w)
	{
	  std::vector<double> res(w->ia);
	  int IO = sc->IO;
	  std::vector<std::optional<int>> na = w->gradeDown();
	  for (int i = 0; i < na.size(); i++)
	  {
		res[i] = na[i].value() + IO;
	  }
	  return std::make_shared<DoubleArr>(res);
	}
}
