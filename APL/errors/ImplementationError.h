#pragma once

#include <APL/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <stdexcept>
#include <memory>

namespace APL::errors
{

	using namespace APL::types;

	class ImplementationError : public APLError
	{
  public:
	  ImplementationError(const std::wstring &s);
	  ImplementationError(const std::wstring &s, std::shared_ptr<Tokenable> fun);
	  ImplementationError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause);
	  ImplementationError(std::runtime_error t);

	protected:
		std::shared_ptr<ImplementationError> shared_from_this()
		{
			return std::static_pointer_cast<ImplementationError>(APLError::shared_from_this());
		}
	};
}
