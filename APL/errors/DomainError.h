#pragma once

#include <APL/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>

namespace APL::errors
{

	using namespace APL::types;

	class DomainError : public APLError
	{
  public:
	  DomainError(const std::wstring &s);
	  DomainError(const std::wstring &s, std::shared_ptr<Tokenable> fun);
	  DomainError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause);

	protected:
		std::shared_ptr<DomainError> shared_from_this()
		{
			return std::static_pointer_cast<DomainError>(APLError::shared_from_this());
		}
	};
}
