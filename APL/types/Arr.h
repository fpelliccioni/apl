#pragma once

#include <APL/Main.h>
#include <APL/Value.h>
#include <APL/Obj.h>
#include <APL/Callable.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <helpers/tangible_rectangular_vectors.h>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types
{

	using namespace APL::errors;
	using namespace APL::types::arrs;


	class Arr : public Value
	{
  public:
	  Arr(std::vector<int> &shape);
	  Arr(std::vector<int> &shape, int ia);
	  Arr(std::vector<int> &shape, int ia, int rank);

	  virtual std::wstring string(bool quote);
	  std::wstring toString() override;
	  std::wstring oneliner(std::vector<int> &where) override;
	  virtual std::shared_ptr<Arr> reverseOn(int dim);


	  static std::shared_ptr<Value> createL(std::vector<std::shared_ptr<Value>> &v, std::vector<int> &sh);

	  static std::shared_ptr<Arr> create(std::vector<std::shared_ptr<Value>> &v);
	  static std::shared_ptr<Arr> create(std::vector<std::shared_ptr<Value>> &v, std::vector<int> &sh);

	  static std::shared_ptr<Arr> create(std::vector<std::shared_ptr<Value>> &v);
	  static std::shared_ptr<Arr> create(std::vector<std::shared_ptr<Value>> &v, std::vector<int> &sh);

	  virtual bool equals(std::shared_ptr<Obj> o);
  protected:
	  int hash = 0;
  public:
	  virtual int hashCode();

  protected:
	  virtual int shapeHash(int hash);

  public:
	  static int prod(std::vector<int> &ia);

	  static void eqShapes(std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  static void eqShapes(std::vector<int> &a, std::vector<int> &w, std::shared_ptr<Callable> blame);

	protected:
		std::shared_ptr<Arr> shared_from_this()
		{
			return std::static_pointer_cast<Arr>(Value::shared_from_this());
		}
	};
}
