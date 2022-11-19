#include <APL/RankError.h>

namespace APL::errors
{
	using namespace APL::types;

	RankError::RankError(const std::wstring &s, std::shared_ptr<Tokenable> fun) : APLError(s, fun)
	{
	}

	RankError::RankError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause) : APLError(s, fun, cause)
	{
	}
}
