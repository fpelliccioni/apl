#pragma once

#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/Value.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types::arrs
{

	using namespace APL::types;


	class HArr : public Arr
	{
  private:
	  const std::vector<std::shared_ptr<Value>> arr;
  public:
	  HArr(std::vector<std::shared_ptr<Value>> &v, std::vector<int> &sh);

	  HArr(std::vector<std::shared_ptr<Value>> &v);
	  HArr(std::vector<std::shared_ptr<Value>> &v);

	  HArr(std::vector<std::shared_ptr<Value>> &v, std::vector<int> &sh);

	  std::vector<int> asIntArrClone() override;

	  int asInt() override;

	  std::shared_ptr<Value> get(int i) override;

	  virtual bool equals(std::shared_ptr<Obj> o);

	  std::wstring asString() override;

	  std::shared_ptr<Value> prototype() override;
	  std::shared_ptr<Value> safePrototype() override;
	  std::vector<std::shared_ptr<Value>> values() override;
	  std::vector<std::shared_ptr<Value>> valuesCopy() override;
	  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;


	protected:
		std::shared_ptr<HArr> shared_from_this()
		{
			return std::static_pointer_cast<HArr>(Arr::shared_from_this());
		}
	};
}
