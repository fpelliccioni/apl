#include <APL/LengthError.h>

namespace APL::errors
{
	using namespace APL::types;

	LengthError::LengthError(const std::wstring &s, std::shared_ptr<Tokenable> fun) : APLError(s, fun)
	{
	}

	LengthError::LengthError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause) : APLError(s, fun, cause)
	{
	}
}
