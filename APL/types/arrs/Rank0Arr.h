#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::arrs
{

	using namespace APL::types;

	class Rank0Arr : public Arr
	{
  public:
	  static const std::vector<int> SHAPE;
	  const std::shared_ptr<Value> item;

	  Rank0Arr(std::shared_ptr<Value> item);

	  std::vector<int> asIntArrClone() override;

	  int asInt() override;

	  std::shared_ptr<Value> get(int i) override;

	  std::wstring asString() override;

	  std::shared_ptr<Value> prototype() override;

	  std::shared_ptr<Value> safePrototype() override;

	  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;

	  std::vector<std::shared_ptr<Value>> valuesCopy() override;

	protected:
		std::shared_ptr<Rank0Arr> shared_from_this()
		{
			return std::static_pointer_cast<Rank0Arr>(Arr::shared_from_this());
		}
	};
}
