#pragma once

#include <APL/Fun.h>
#include <APL/Scope.h>
#include <APL/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::dimensions
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;

	class DervDimFn : public Fun
	{
  private:
	  const int IO;
	  const std::shared_ptr<Fun> f;
	  const std::vector<int> raw;
//JAVA TO C++ CONVERTER NOTE: Field name conflicts with a method name of the current type:
	  const std::vector<int> dims_Conflict;

  public:
	  std::wstring repr() override;

	  DervDimFn(std::shared_ptr<Fun> f, std::vector<int> &raw, std::shared_ptr<Scope> sc);

	  virtual std::vector<int> dims(int rank);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  virtual int singleDim(int rank);
	  virtual int singleDim();

	  virtual std::wstring format();

	protected:
		std::shared_ptr<DervDimFn> shared_from_this()
		{
			return std::static_pointer_cast<DervDimFn>(Fun::shared_from_this());
		}
	};
}
