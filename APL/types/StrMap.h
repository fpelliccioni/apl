#pragma once

#include <APL/types/arrs/HArr.h>
#include <APL/types/APLMap.h>
#include <APL/types/Obj.h>
#include <APL/Scope.h>
#include <APL/types/Value.h>
#include <APL/types/Arr.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types
{

	using namespace APL;


	class StrMap : public APLMap
	{
  public:
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: public final HashMap<String, Obj> vals;
	  std::unordered_map<std::wstring, std::shared_ptr<Obj>> vals;
	  // public final Scope sc;

	  StrMap(std::shared_ptr<Scope> sc);

	  StrMap(std::unordered_map<std::wstring, std::shared_ptr<Obj>> &vals);

	  StrMap();

	  // public StrMap(Scope sc, HashMap<String, Obj> vals) {
	  //   this.sc = sc;
	  //   this.vals = vals;
	  // }


	  std::shared_ptr<Obj> getRaw(std::shared_ptr<Value> k) override;
	  std::shared_ptr<Obj> getRaw(const std::wstring &k) override;

	  void set(std::shared_ptr<Value> k, std::shared_ptr<Obj> v) override;

	  virtual void setStr(const std::wstring &k, std::shared_ptr<Obj> v);

	  std::shared_ptr<Arr> allValues() override;

	  std::shared_ptr<Arr> allKeys() override;

	  std::shared_ptr<Arr> kvPair() override;

	  int size() override;

	  virtual bool equals(std::shared_ptr<Obj> o);

	  virtual std::wstring toString();

	protected:
		std::shared_ptr<StrMap> shared_from_this()
		{
			return std::static_pointer_cast<StrMap>(APLMap::shared_from_this());
		}
	};
}
