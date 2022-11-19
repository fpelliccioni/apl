#pragma once

#include <APL/APLError.h>
#include <APL/types/Callable.h>
#include <APL/types/Tokenable.h>
#include <string>
#include <memory>

namespace APL::errors
{

	using namespace APL::types;

	class IncorrectArgsError : public APLError
	{
  public:
	  IncorrectArgsError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause);

	protected:
		std::shared_ptr<IncorrectArgsError> shared_from_this()
		{
			return std::static_pointer_cast<IncorrectArgsError>(APLError::shared_from_this());
		}
	};
}
