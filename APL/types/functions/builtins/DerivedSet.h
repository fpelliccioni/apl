#pragma once

#include <APL/types/functions/builtins/AbstractSet.h>
#include <APL/types/functions/builtins/SetBuiltin.h>
#include <APL/types/Fun.h>
#include <APL/types/Obj.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins
{

	using namespace APL::types;

	class DerivedSet : public AbstractSet
	{

  private:
	  const std::shared_ptr<SetBuiltin> s;
	  const std::shared_ptr<Fun> f;

  public:
	  DerivedSet(std::shared_ptr<SetBuiltin> s, std::shared_ptr<Fun> f);

	  std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> a, std::shared_ptr<Obj> w, bool update) override;

	  std::wstring toString() override;

	protected:
		std::shared_ptr<DerivedSet> shared_from_this()
		{
			return std::static_pointer_cast<DerivedSet>(AbstractSet::shared_from_this());
		}
	};
}
