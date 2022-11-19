#include <APL/NYIError.h>

namespace APL::errors
{
	using namespace APL::types;

	NYIError::NYIError(const std::wstring &s) : APLError(s)
	{
	}

	NYIError::NYIError(const std::wstring &s, std::shared_ptr<Tokenable> fun) : APLError(s, fun)
	{
	}

	NYIError::NYIError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause) : APLError(s, fun, cause)
	{
	}
}
