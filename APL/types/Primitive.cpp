#include <APL/types/Primitive.h>

namespace APL::types
{
    using DomainError = APL::errors::DomainError;
const std::vector<int> Primitive::SHAPE = std::vector<int>(0);

    Primitive::Primitive() : APL::types::Value(SHAPE, 1, 0)
    {
    }

    std::shared_ptr<APL::types::Value> Primitive::get(int i)
    {
      return shared_from_this();
    }

    std::shared_ptr<APL::types::Value> Primitive::first()
    {
      return shared_from_this();
    }

    std::vector<int> Primitive::asIntArrClone()
    {
      throw DomainError(StringHelper::wstring_to_string(L"Using " + this->oneliner() + L" as integer array", shared_from_this()));
    }

    std::vector<int> Primitive::asIntVec()
    {
      throw DomainError(StringHelper::wstring_to_string(L"Using " + this->oneliner() + L" as integer vector", shared_from_this()));
    }

    int Primitive::asInt()
    {
      throw DomainError(StringHelper::wstring_to_string(L"Using " + this->oneliner() + L" as integer", shared_from_this()));
    }

    std::string Primitive::asString()
    {
      throw DomainError(StringHelper::wstring_to_string(L"Using " + this->oneliner() + L" as string", shared_from_this()));
    }

    std::shared_ptr<APL::types::Value> Primitive::prototype()
    {
      std::shared_ptr<APL::types::Value> v = safePrototype();
      if (v->empty())
      {
          throw DomainError(StringHelper::wstring_to_string(L"Getting prototype of " + shared_from_this(), shared_from_this()));
      }
      return v;
    }

    std::shared_ptr<APL::types::Value> Primitive::safePrototype()
    {
      return nullptr;
    }

    std::shared_ptr<APL::types::Value> Primitive::squeeze()
    { // primitives are already pretty squeezed
      return shared_from_this();
    }
}
