#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>

namespace APL::errors
{

	using namespace APL::types;

	class RankError : public APLError
	{
	  // public RankError(String s) {
	  //   super(s);
	  // }
  public:
	  RankError(const std::wstring &s, std::shared_ptr<Tokenable> fun);
	  RankError(const std::wstring &s, std::shared_ptr<Callable> fun, std::shared_ptr<Tokenable> cause);

	protected:
		std::shared_ptr<RankError> shared_from_this()
		{
			return std::static_pointer_cast<RankError>(APLError::shared_from_this());
		}
	};
}
