#include <APL/GradeUpBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using Scope = APL::Scope;
	using APL::types::Value = APL::types::APL::types::Value;
	using DoubleArr = APL::types::arrs::DoubleArr;
	using Builtin = APL::types::functions::Builtin;

	std::string GradeUpBuiltin::repr()
	{
	  return L"⍋";
	}

	GradeUpBuiltin::GradeUpBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
	{
	}

	std::shared_ptr<APL::types::Value> GradeUpBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  std::vector<double> res(w->ia);
	  int IO = sc->IO;
	  std::vector<std::optional<int>> na = w->gradeUp();
	  for (int i = 0; i < na.size(); i++)
	  {
		res[i] = na[i].value() + IO;
	  }
	  return std::make_shared<DoubleArr>(res);
	}
}
