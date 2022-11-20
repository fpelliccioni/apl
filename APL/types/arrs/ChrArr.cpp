#include <APL/types/arrs/ChrArr.h>
#include <APL/types/Char.h>

namespace APL::types::arrs
{
	using Main = APL::Main;
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;

	ChrArr::ChrArr(const std::wstring &s) : Arr(std::vector<int>{s.length()}, s.length(), 1)
	{
	  this->s = s;
	}

	ChrArr::ChrArr(const std::wstring &s, std::vector<int> &sh) : Arr(sh, s.length(), sh.size())
	{
	  assert(Main::enclosePrimitives || sh.size() != 0);
	  this->s = s;
	}

	ChrArr::ChrArr(std::vector<wchar_t> &arr, std::vector<int> &sh) : ChrArr(std::wstring(arr), sh)
	{
	}

	ChrArr::ChrArr(std::vector<wchar_t> &arr) : ChrArr(std::wstring(arr))
	{
	}

	std::vector<int> ChrArr::asIntArrClone()
	{
	  throw DomainError(L"Using character array as integer array", shared_from_this());
	}

	int ChrArr::asInt()
	{
	  throw DomainError(L"Using character array as integer", shared_from_this());
	}

	std::shared_ptr<Value> ChrArr::get(int i)
	{
	  return Char::of(s[i]);
	}

	std::shared_ptr<Value> ChrArr::first()
	{
	  if (ia > 0)
	  {
		  return Char::of(s[0]);
	  }
	  return Char::SPACE;
	}

	std::wstring ChrArr::asString()
	{
	  if (rank > 1)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"Using rank " + std::to_wstring(rank) + L" character array as string", shared_from_this()));
	  }
	  return s;
	}

	std::shared_ptr<Value> ChrArr::prototype()
	{
	  return Char::SPACE;
	}

	std::shared_ptr<Value> ChrArr::safePrototype()
	{
	  return Char::SPACE;
	}

	std::shared_ptr<Value> ChrArr::ofShape(std::vector<int> &sh)
	{
	  if (sh.empty() && !Main::enclosePrimitives)
	  {
		  return this->operator[](0);
	  }
	  return std::make_shared<ChrArr>(s, sh);
	}

	std::shared_ptr<Value> ChrArr::squeeze()
	{
	  return shared_from_this();
	}

	int ChrArr::hashCode()
	{
	  if (hash == 0)
	  {
		for (auto c : std::vector<wchar_t>(s.begin(), s.end()))
		{
		  hash = hash * 31 + c;
		}
		hash = shapeHash(hash);
	  }
	  return hash;
	}
}
