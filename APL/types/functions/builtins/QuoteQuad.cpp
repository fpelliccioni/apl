#include <APL/QuoteQuad.h>
#include <APL/Main.h>

namespace APL::types::functions::builtins
{
    // using namespace APL;
    // using namespace APL::types;

    QuoteQuad::QuoteQuad(std::shared_ptr<Scope> sc) : Settable(nullptr), sc(sc)
    {
    }

    void QuoteQuad::set(std::shared_ptr<APL::types::Obj> v, std::shared_ptr<APL::types::Callable> blame)
    {
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
      sc->sys->print(v->toString());
    }

    std::shared_ptr<APL::types::Obj> QuoteQuad::get()
    {
      return Main::toAPL(sc->sys->input());
    }

    APL::Type QuoteQuad::type()
    {
      return Type::gettable;
    }

    std::string QuoteQuad::toString()
    {
      return L"⍞";
    }
}
