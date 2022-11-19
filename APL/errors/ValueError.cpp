#include <APL/ValueError.h>

namespace APL::errors
{
	using namespace APL::types;

	ValueError::ValueError(const std::wstring &s) : APLError(s)
	{
	}

	ValueError::ValueError(const std::wstring &s, std::shared_ptr<Tokenable> fun) : APLError(s, fun)
	{
	}

	ValueError::ValueError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause) : APLError(s, fun, cause)
	{
	}
}
