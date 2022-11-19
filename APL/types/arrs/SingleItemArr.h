#pragma once

#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/Arr.h>
#include <APL/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types::arrs
{

	using namespace APL::types;

	using Iterator = java::util::Iterator;

	class SingleItemArr : public Arr
	{
  private:
	  const std::shared_ptr<Value> item;

  public:
	  SingleItemArr(std::shared_ptr<Value> item, std::vector<int> &shape);

	  static std::shared_ptr<Value> maybe(std::shared_ptr<Value> item, std::vector<int> &sh);

	  std::vector<int> asIntArrClone() override;

	  int asInt() override;

	  std::shared_ptr<Value> get(int i) override;

	  std::shared_ptr<Value> first() override;

	  std::wstring asString() override;

	  std::shared_ptr<Value> prototype() override;
	  std::shared_ptr<Value> safePrototype() override;
	  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;

	  bool quickDoubleArr() override;
	  std::vector<std::shared_ptr<Value>> valuesCopy() override;

	  double sum() override;

	  std::vector<double> asDoubleArr() override;

	  std::vector<double> asDoubleArrClone() override;

	  std::shared_ptr<Value> squeeze() override;

	  std::wstring oneliner(std::vector<int> &where) override;

	  std::shared_ptr<Iterator<std::shared_ptr<Value>>> iterator() override;

  private:
	  class IteratorAnonymousInnerClass : public std::enable_shared_from_this<IteratorAnonymousInnerClass>, public Iterator<std::shared_ptr<Value>>
	  {
	  private:
		  std::shared_ptr<SingleItemArr> outerInstance;

	  public:
		  IteratorAnonymousInnerClass(std::shared_ptr<SingleItemArr> outerInstance);

		  int i = 0;
		  bool hasNext();

		  std::shared_ptr<Value> next();
	  };

	protected:
		std::shared_ptr<SingleItemArr> shared_from_this()
		{
			return std::static_pointer_cast<SingleItemArr>(Arr::shared_from_this());
		}
	};
}
