#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>

namespace APL::errors
{

	using namespace APL::types;

	class NYIError : public APLError
	{ // AKA LazyError
  public:
	  NYIError(const std::wstring &s);
	  NYIError(const std::wstring &s, std::shared_ptr<Tokenable> fun);
	  NYIError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause);

	protected:
		std::shared_ptr<NYIError> shared_from_this()
		{
			return std::static_pointer_cast<NYIError>(APLError::shared_from_this());
		}
	};
}
