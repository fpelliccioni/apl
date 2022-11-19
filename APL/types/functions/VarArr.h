#pragma once

#include <APL/errors/LengthError.h>
#include <APL/builtins/SetBuiltin.h>
#include <APL/Settable.h>
#include <APL/Obj.h>
#include <APL/Arr.h>
#include <APL/Type.h>
#include <APL/Callable.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

namespace APL::types::functions
{

	using namespace APL;
	using namespace APL::types;
	using namespace APL::types::arrs;


	class VarArr : public Settable
	{
  public:
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: public final ArrayList<Obj> arr;
	  std::vector<std::shared_ptr<Obj>> arr;
	  const int ia;
	  VarArr(std::vector<std::shared_ptr<Obj>> &arr);

	  std::shared_ptr<Arr> get() override;

	  Type type() override;

	  void set(std::shared_ptr<Obj> v, std::shared_ptr<Callable> blame) override;

	  virtual std::wstring toString();

	  static std::shared_ptr<Obj> of(std::vector<std::shared_ptr<Obj>> &vs);

	  virtual void set(std::shared_ptr<Obj> w, bool update);

	protected:
		std::shared_ptr<VarArr> shared_from_this()
		{
			return std::static_pointer_cast<VarArr>(Settable::shared_from_this());
		}
	};
}
