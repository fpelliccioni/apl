#pragma once

#include <APL/Type.h>
#include <APL/arrs/SingleItemArr.h>
#include <APL/Primitive.h>
#include <APL/Value.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types
{

	using Type = APL::Type;

	class Null : public Primitive
	{
  public:
	  static const std::shared_ptr<Null> NULL;
  private:
	  Null();

  public:
	  virtual std::wstring toString();

	  Type type() override;

	  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;

	  virtual int hashCode();

	protected:
		std::shared_ptr<Null> shared_from_this()
		{
			return std::static_pointer_cast<Null>(Primitive::shared_from_this());
		}
	};
}
