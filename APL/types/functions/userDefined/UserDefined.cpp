#include <APL/UserDefined.h>
#include <APL/Dfn.h>
#include <APL/Dmop.h>
#include <APL/Ddop.h>

namespace APL::types::functions::userDefined
{
    // using namespace APL;
    using Token = APL::tokenizer::Token;
    // using namespace APL::tokenizer::types;
    using Obj = APL::types::Obj;

    std::shared_ptr<APL::types::Obj> UserDefined::of(std::shared_ptr<DfnTok> ts, std::shared_ptr<Scope> sc)
    {
      Type type = funType(ts, true);
      switch (type)
      {
        case APL::Type::fn:
            return std::make_shared<Dfn>(ts, sc);
        case APL::Type::mop:
            return std::make_shared<Dmop>(ts, sc);
        case APL::Type::dop:
            return std::make_shared<Ddop>(ts, sc);
        default :
            throw IllegalStateException();
      }
    }
}
