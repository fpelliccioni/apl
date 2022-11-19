#pragma once

#include <APL/Main.h>
#include <APL/arrs/ChrArr.h>
#include <APL/Primitive.h>
#include <APL/Value.h>
#include <APL/Obj.h>
#include <string>
#include <vector>
#include <cctype>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types
{



	class Char : public Primitive
	{
  public:
	  wchar_t chr = L'\0';
	  static std::vector<std::shared_ptr<Char>> ASCII;
	  private:
		  class StaticConstructor : public std::enable_shared_from_this<StaticConstructor>
		  {
		  public:
			  StaticConstructor();
		  };

	  private:
		  static Char::StaticConstructor staticConstructor;


  public:
	  static const std::shared_ptr<Char> SPACE;

	  Char(wchar_t c);

	  static std::shared_ptr<Char> of(wchar_t c);

	  virtual std::shared_ptr<Char> upper();

	  virtual std::shared_ptr<Char> lower();

	  virtual std::shared_ptr<Char> swap();

	  virtual int getCase();

	  std::wstring toString() override;
	  std::wstring oneliner(std::vector<int> &ignored) override;

	  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;

	  virtual int compareTo(std::shared_ptr<Char> v);


	  virtual bool equals(std::shared_ptr<Obj> c);

	  std::wstring asString() override;

	  virtual int hashCode();

	  std::shared_ptr<Value> safePrototype() override;

	protected:
		std::shared_ptr<Char> shared_from_this()
		{
			return std::static_pointer_cast<Char>(Primitive::shared_from_this());
		}
	};
}
