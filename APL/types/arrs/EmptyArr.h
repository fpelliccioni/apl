#pragma once

#include <APL/Arr.h>
#include <APL/Value.h>
#include <string>
#include <vector>
#include <helpers/tangible_exception_helper.h>
#include <cassert>
#include <memory>

namespace APL::types::arrs
{

	using namespace APL::errors;
	using namespace APL::types;

	using Iterator = java::util::Iterator;

	class EmptyArr : public Arr
	{
  public:
	  static const std::vector<int> SHAPE0;
	  static const std::shared_ptr<EmptyArr> SHAPE0Q;
	  static const std::shared_ptr<EmptyArr> SHAPE0N;
	  static const std::vector<int> NOINTS;
  private:
	  const std::shared_ptr<Value> proto;
  public:
	  EmptyArr(std::vector<int> &sh, std::shared_ptr<Value> proto);

	  std::vector<int> asIntArrClone() override;

	  int asInt() override;

	  bool quickDoubleArr() override;

	  std::vector<double> asDoubleArr() override;

	  std::shared_ptr<Value> get(int i) override;

	  std::wstring asString() override;

	  std::shared_ptr<Value> prototype() override;
	  std::shared_ptr<Value> safePrototype() override;

	  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;

  private:
	  static const std::vector<std::shared_ptr<Value>> NO_VALUES;
  public:
	  std::vector<std::shared_ptr<Value>> valuesCopy() override;

	  std::shared_ptr<Value> squeeze() override;



  private:
	  static const std::shared_ptr<Iterator<std::shared_ptr<Value>>> EIT;

  private:
	  class IteratorAnonymousInnerClass : public std::enable_shared_from_this<IteratorAnonymousInnerClass>, public Iterator<std::shared_ptr<Value>>
	  {
	  public:
		  bool hasNext();
		  std::shared_ptr<Value> next();
	  };
  public:
	  std::shared_ptr<Iterator<std::shared_ptr<Value>>> iterator() override;

	protected:
		std::shared_ptr<EmptyArr> shared_from_this()
		{
			return std::static_pointer_cast<EmptyArr>(Arr::shared_from_this());
		}
	};
}
