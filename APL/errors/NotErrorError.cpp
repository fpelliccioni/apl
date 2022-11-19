#include <APL/NotErrorError.h>

namespace APL::errors
{
	using Obj = APL::types::Obj;

	NotErrorError::NotErrorError(const std::wstring &msg, std::shared_ptr<Obj> cause) : APLError(msg)
	{
	  this->cause = cause;
	}
}
