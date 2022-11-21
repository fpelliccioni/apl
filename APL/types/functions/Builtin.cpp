#include <APL/types/functions/Builtin.h>

namespace APL::types::functions
{
    using Scope = APL::Scope;
    using Fun = APL::types::Fun;

    Builtin::Builtin(std::shared_ptr<Scope> sc) : APL::types::Fun(sc)
    {
    }

    Builtin::Builtin() : APL::types::Fun(nullptr)
    {
    }
}
