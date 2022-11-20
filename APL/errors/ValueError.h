#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>

namespace APL::errors
{

	using namespace APL::types;

	class ValueError : public APLError
	{
  public:
	  ValueError(const std::wstring &s);
	  ValueError(const std::wstring &s, std::shared_ptr<Tokenable> fun);
	  ValueError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause);

	protected:
		std::shared_ptr<ValueError> shared_from_this()
		{
			return std::static_pointer_cast<ValueError>(APLError::shared_from_this());
		}
	};
}
