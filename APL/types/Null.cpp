#include <APL/Null.h>

namespace APL::types
{
    using Type = APL::Type;
    using SingleItemArr = APL::types::arrs::SingleItemArr;
const std::shared_ptr<Null> Null::NULL = std::make_shared<Null>();

    Null::Null()
    {
    }

    std::string Null::toString()
    {
      return L"⎕NULL";
    }

    APL::Type Null::type()
    {
      return Type::nul;
    }

    std::shared_ptr<APL::types::Value> Null::ofShape(std::vector<int> &sh)
    {
      return SingleItemArr::maybe(shared_from_this(), sh);
    }

    int Null::hashCode()
    {
      return 387678968; // random yay
    }
}
