#include <APL/types/arrs/ChrArr.h>
#include <APL/types/Char.h>

namespace APL::types::arrs
{
    using Main = APL::Main;
    using DomainError = APL::errors::DomainError;
    // using namespace APL::types;

    APL::types::arrs::ChrArr::APL::types::arrs::ChrArr(std::string const& s) : Arr(std::vector<int>{s.length()}, s.length(), 1)
    {
      this->s = s;
    }

    APL::types::arrs::ChrArr::APL::types::arrs::ChrArr(std::string const& s, std::vector<int> &sh) : Arr(sh, s.length(), sh.size())
    {
      assert(Main::enclosePrimitives || sh.size() != 0);
      this->s = s;
    }

    APL::types::arrs::ChrArr::APL::types::arrs::ChrArr(std::vector<wchar_t> &arr, std::vector<int> &sh) : APL::types::arrs::ChrArr(std::string(arr), sh)
    {
    }

    APL::types::arrs::ChrArr::APL::types::arrs::ChrArr(std::vector<wchar_t> &arr) : APL::types::arrs::ChrArr(std::string(arr))
    {
    }

    std::vector<int> APL::types::arrs::ChrArr::asIntArrClone()
    {
      throw DomainError(L"Using character array as integer array", shared_from_this());
    }

    int APL::types::arrs::ChrArr::asInt()
    {
      throw DomainError(L"Using character array as integer", shared_from_this());
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::ChrArr::get(int i)
    {
      return Char::of(s[i]);
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::ChrArr::first()
    {
      if (ia > 0)
      {
          return Char::of(s[0]);
      }
      return Char::SPACE;
    }

    std::string APL::types::arrs::ChrArr::asString()
    {
      if (rank > 1)
      {
          throw DomainError(StringHelper::wstring_to_string(L"Using rank " + std::to_wstring(rank) + L" character array as string", shared_from_this()));
      }
      return s;
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::ChrArr::prototype()
    {
      return Char::SPACE;
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::ChrArr::safePrototype()
    {
      return Char::SPACE;
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::ChrArr::ofShape(std::vector<int> &sh)
    {
      if (sh.empty() && !Main::enclosePrimitives)
      {
          return this->operator[](0);
      }
      return std::make_shared<APL::types::arrs::ChrArr>(s, sh);
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::ChrArr::squeeze()
    {
      return shared_from_this();
    }

    int APL::types::arrs::ChrArr::hashCode()
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
