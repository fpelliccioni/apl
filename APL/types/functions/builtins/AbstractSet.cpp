#include <APL/types/functions/builtins/AbstractSet.h>

namespace APL::types::functions::builtins
{
    using Type = APL::Type;
    // using namespace APL::types;

    AbstractSet::AbstractSet() : Callable(nullptr)
    {
    }

    APL::Type AbstractSet::type()
    {
      return Type::set;
    }
}
