#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::errors
{

	using namespace APL::types;

	class SyntaxError : public APLError
	{
  public:
	  SyntaxError(const std::wstring &s);
	  SyntaxError(const std::wstring &s, std::shared_ptr<Tokenable> fun);
	  SyntaxError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause);

	  static void must(bool b, const std::wstring &msg);

	protected:
		std::shared_ptr<SyntaxError> shared_from_this()
		{
			return std::static_pointer_cast<SyntaxError>(APLError::shared_from_this());
		}
	};
}
