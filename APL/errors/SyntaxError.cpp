#include <APL/SyntaxError.h>

namespace APL::errors
{
	using namespace APL::types;

	SyntaxError::SyntaxError(const std::wstring &s) : APLError(s)
	{
	}

	SyntaxError::SyntaxError(const std::wstring &s, std::shared_ptr<Tokenable> fun) : APLError(s, fun)
	{
	}

	SyntaxError::SyntaxError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause) : APLError(s, fun, cause)
	{
	}

	void SyntaxError::must(bool b, const std::wstring &msg)
	{
	  if (!b)
	  {
		  throw SyntaxError(StringHelper::wstring_to_string(msg));
	  }
	}
}
