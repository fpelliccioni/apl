#include <APL/IncorrectArgsError.h>

namespace APL::errors
{
	using namespace APL::types;

	IncorrectArgsError::IncorrectArgsError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause) : APLError(s, fun, cause)
	{
	}
}
