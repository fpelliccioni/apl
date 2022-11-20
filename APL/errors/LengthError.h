#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>

namespace APL::errors
{

	using namespace APL::types;

	class LengthError : public APLError
	{
	  // public LengthError(String s) {
	  //   super(s);
	  // }
  public:
	  LengthError(const std::wstring &s, std::shared_ptr<Tokenable> fun);
	  LengthError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause);

	protected:
		std::shared_ptr<LengthError> shared_from_this()
		{
			return std::static_pointer_cast<LengthError>(APLError::shared_from_this());
		}
	};
}
