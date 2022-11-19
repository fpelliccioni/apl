#include <APL/DomainError.h>

namespace APL::errors
{
	using namespace APL::types;

	DomainError::DomainError(const std::wstring &s) : APLError(s)
	{
	}

	DomainError::DomainError(const std::wstring &s, std::shared_ptr<Tokenable> fun) : APLError(s, fun)
	{
	}

	DomainError::DomainError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause) : APLError(s, fun, cause)
	{
	}
}
