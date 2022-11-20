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

namespace APL::types::arrs
{

	using namespace APL::types;


	class DoubleArr : public Arr
	{
  public:
	  static const std::vector<double> EMPTY;
	  const std::vector<double> arr;
	  DoubleArr(std::vector<double> &arr, std::vector<int> &sh);
	  DoubleArr(std::vector<double> &arr);

	  DoubleArr(std::vector<int> &arr);
	  DoubleArr(std::vector<signed char> &arr);

	  DoubleArr(std::vector<double> &arrl);

	  static std::shared_ptr<Value> safe(std::vector<double> &vs, std::vector<int> &sh);

	  std::vector<int> asIntArrClone() override;

	  int asInt() override;

	  std::shared_ptr<Value> get(int i) override;

	  std::shared_ptr<Value> first() override;

	  std::wstring asString() override;

	  std::shared_ptr<Value> prototype() override;
	  std::shared_ptr<Value> safePrototype() override;

	  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;

	  double sum() override;

	  std::vector<double> asDoubleArr() override;
	  std::vector<double> asDoubleArrClone() override;

	  bool quickDoubleArr() override;

	  std::shared_ptr<Value> squeeze() override;

	  std::vector<std::shared_ptr<Value>> valuesCopy() override;

	  std::shared_ptr<Arr> reverseOn(int dim) override;

	  virtual bool equals(std::shared_ptr<Obj> o);
	  virtual int hashCode();

	protected:
		std::shared_ptr<DoubleArr> shared_from_this()
		{
			return std::static_pointer_cast<DoubleArr>(Arr::shared_from_this());
		}
	};
}
