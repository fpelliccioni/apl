#include <APL/ImplementationError.h>

namespace APL::errors
{
	using namespace APL::types;

	ImplementationError::ImplementationError(const std::wstring &s) : APLError(s)
	{
	}

	ImplementationError::ImplementationError(const std::wstring &s, std::shared_ptr<Tokenable> fun) : APLError(s, fun)
	{
	}

	ImplementationError::ImplementationError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause) : APLError(s, fun, cause)
	{
	}

	ImplementationError::ImplementationError(std::runtime_error t) : APLError(t.what())
	{
	  initCause(t);
	}
}
