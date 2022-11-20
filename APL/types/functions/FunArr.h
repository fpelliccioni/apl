#pragma once

#include <APL/types/Fun.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types::functions
{

	using namespace APL::types;

	class FunArr : public Fun
	{
  private:
	  const std::vector<std::shared_ptr<Obj>> os;

  public:
	  FunArr(std::vector<std::shared_ptr<Obj>> &os);

	  std::wstring repr() override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<FunArr> shared_from_this()
		{
			return std::static_pointer_cast<FunArr>(Fun::shared_from_this());
		}
	};
}
