#pragma once

#include <APL/types/Obj.h>
#include <APL/errors/APLError.h>
#include <string>
#include <memory>

namespace APL::errors
{

	using Obj = APL::types::Obj;

	class NotErrorError : public APLError
	{

  public:
	  NotErrorError(const std::wstring &msg, std::shared_ptr<Obj> cause);

	protected:
		std::shared_ptr<NotErrorError> shared_from_this()
		{
			return std::static_pointer_cast<NotErrorError>(APLError::shared_from_this());
		}
	};
}
