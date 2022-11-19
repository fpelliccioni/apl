#pragma once

#include <APL/Obj.h>
#include <APL/Type.h>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types::arrs;



	class Value : public Obj, public std::vector<std::shared_ptr<Value>>
	{
  public:
	  const std::vector<int> shape;
	  const int rank;
	  const int ia; // item amount
	  Value(std::vector<int> &shape);
	  Value(std::vector<int> &shape, int ia, int rank);
	  virtual std::vector<int> asIntVec();
	  virtual std::vector<int> asIntArrClone() = 0;
	  virtual std::vector<int> asIntArr();
	  virtual int asInt() = 0;
	  virtual bool scalar();
	  virtual std::shared_ptr<Value> first();
	  virtual std::shared_ptr<Value> get(int i) = 0; // WARNING: UNSAFE; doesn't need to throw for out-of-bounds



	  virtual int compareTo(std::shared_ptr<Value> r);


	  virtual std::wstring asString() = 0;


	  virtual std::vector<std::optional<int>> gradeUp();
	  virtual std::vector<std::optional<int>> gradeDown();

	  virtual std::vector<int> eraseDim(int place);
	  Type type() override;

	  virtual std::shared_ptr<Value> prototype() = 0; // what to append to this array
	  virtual std::shared_ptr<Value> safePrototype() = 0;

	  virtual std::wstring oneliner(std::vector<int> &where);

	  virtual std::wstring oneliner();


	  virtual std::vector<std::shared_ptr<Value>> values();
	  virtual std::vector<std::shared_ptr<Value>> valuesCopy();

	  std::shared_ptr<Iterator<std::shared_ptr<Value>>> iterator() override;

	  virtual std::shared_ptr<Value> ind(std::vector<std::vector<double>> &ind, int id, int IO);

  public:
	  class ValueIterator : public std::enable_shared_from_this<ValueIterator>, public Iterator<std::shared_ptr<Value>>
	  {
	  private:
		  std::shared_ptr<Value> outerInstance;

	  public:
		  ValueIterator(std::shared_ptr<Value> outerInstance);

		int c = 0;
		bool hasNext() override;

		std::shared_ptr<Value> next() override;
	  };

  public:
	  virtual std::shared_ptr<Value> at(std::vector<int> &pos, int IO);
	  virtual std::shared_ptr<Value> at(std::vector<int> &pos, std::shared_ptr<Value> def);
	  virtual std::shared_ptr<Value> simpleAt(std::vector<int> &pos);

	  virtual std::shared_ptr<Value> ofShape(std::vector<int> &sh) = 0; // don't call with ×/sh ≠ ×/shape!

	  virtual double sum();
	  virtual std::vector<double> asDoubleArr();
	  virtual std::vector<double> asDoubleArrClone();
	  virtual double asDouble();
	  virtual bool quickDoubleArr();
	  virtual std::shared_ptr<Value> squeeze();

	  virtual std::shared_ptr<Value> cut(int s, int len, std::vector<int> &sh);

	protected:
		std::shared_ptr<Value> shared_from_this()
		{
			return std::static_pointer_cast<Value>(Obj::shared_from_this());
		}
	};
}
