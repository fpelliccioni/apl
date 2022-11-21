//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/Exec.h>
#include <APL/Main.h>
#include <APL/tokenizer/types/OpTok.h>
#include <APL/tokenizer/types/SetTok.h>
#include <APL/tokenizer/types/NameTok.h>
#include <APL/types/functions/builtins/fns/PlusBuiltin.h>
#include <APL/types/functions/builtins/fns/MinusBuiltin.h>
#include <APL/types/functions/builtins/dops/DotBuiltin.h>
#include <APL/types/APLMap.h>
#include <APL/errors/SyntaxError.h>
#include <APL/Type.h>
#include <APL/types/functions/VarArr.h>
#include <APL/types/Variable.h>
#include <APL/types/dimensions/Brackets.h>
#include <APL/types/dimensions/DervDimFn.h>
#include <APL/types/dimensions/DervDimMop.h>
#include <APL/types/dimensions/DervDimDop.h>
#include <APL/types/dimensions/Pick.h>
#include <APL/types/functions/builtins/fns/RShoeUBBuiltin.h>
#include <APL/types/functions/builtins/DerivedSet.h>
#include <APL/types/functions/builtins/SetBuiltin.h>
#include <APL/types/functions/trains/Fork.h>
#include <APL/types/functions/trains/Atop.h>
#include <APL/types/functions/builtins/dops/JotBuiltin.h>
#include <APL/types/functions/builtins/mops/TableBuiltin.h>
#include <APL/types/functions/builtins/fns/MulBuiltin.h>
#include <APL/types/functions/builtins/fns/DivBuiltin.h>
#include <APL/types/functions/builtins/fns/StarBuiltin.h>
#include <APL/types/functions/builtins/fns/LogBuiltin.h>
#include <APL/types/functions/builtins/fns/RootBuiltin.h>
#include <APL/types/functions/builtins/fns/CeilingBuiltin.h>
#include <APL/types/functions/builtins/fns/FloorBuiltin.h>
#include <APL/types/functions/builtins/fns/StileBuiltin.h>
#include <APL/types/functions/builtins/fns/AndBuiltin.h>
#include <APL/types/functions/builtins/fns/OrBuiltin.h>
#include <APL/types/functions/builtins/fns/NandBuiltin.h>
#include <APL/types/functions/builtins/fns/NorBuiltin.h>
#include <APL/types/functions/builtins/fns/UTackBuiltin.h>
#include <APL/types/functions/builtins/fns/DTackBuiltin.h>
#include <APL/types/functions/builtins/fns/TildeBuiltin.h>
#include <APL/types/functions/builtins/fns/TrigBuiltin.h>
#include <APL/types/functions/builtins/fns/ExclBuiltin.h>
#include <APL/types/functions/builtins/fns/EpsilonBuiltin.h>
#include <APL/types/functions/builtins/fns/FindBuiltin.h>
#include <APL/types/functions/builtins/fns/LShoeBuiltin.h>
#include <APL/types/functions/builtins/fns/RShoeBuiltin.h>
#include <APL/types/functions/builtins/fns/DShoeBuiltin.h>
#include <APL/types/functions/builtins/fns/UShoeBuiltin.h>
#include <APL/types/functions/builtins/fns/SquadBuiltin.h>
#include <APL/types/functions/builtins/fns/IotaBuiltin.h>
#include <APL/types/functions/builtins/fns/IotaUBBuiltin.h>
#include <APL/types/functions/builtins/fns/RhoBuiltin.h>
#include <APL/types/functions/builtins/fns/CatBuiltin.h>
#include <APL/types/functions/builtins/fns/TallyBuiltin.h>
#include <APL/types/functions/builtins/fns/DepthBuiltin.h>
#include <APL/types/functions/builtins/fns/RTackBuiltin.h>
#include <APL/types/functions/builtins/fns/LTackBuiltin.h>
#include <APL/types/functions/builtins/fns/UpArrowBuiltin.h>
#include <APL/types/functions/builtins/fns/DownArrowBuiltin.h>
#include <APL/types/functions/builtins/fns/RandBuiltin.h>
#include <APL/types/functions/builtins/fns/CommaBarBuiltin.h>
#include <APL/types/functions/builtins/fns/TransposeBuiltin.h>
#include <APL/types/functions/builtins/fns/FlipBuiltin.h>
#include <APL/types/functions/builtins/fns/ReverseBuiltin.h>
#include <APL/types/functions/builtins/fns/EllipsisBuiltin.h>
#include <APL/types/functions/builtins/fns/SemiUBBuiltin.h>
#include <APL/types/functions/builtins/fns/FormatBuiltin.h>
#include <APL/types/functions/builtins/fns/EvalBuiltin.h>
#include <APL/types/functions/builtins/fns/GradeUpBuiltin.h>
#include <APL/types/functions/builtins/fns/GradeDownBuiltin.h>
#include <APL/types/functions/builtins/fns/ReplicateBuiltin.h>
#include <APL/types/functions/builtins/fns/ExpandBuiltin.h>
#include <APL/types/functions/builtins/fns/LShoeStileBuiltin.h>
#include <APL/types/functions/builtins/fns/MergeBuiltin.h>
#include <APL/types/functions/builtins/fns/LTBuiltin.h>
#include <APL/types/functions/builtins/fns/LEBuiltin.h>
#include <APL/types/functions/builtins/fns/EQBuiltin.h>
#include <APL/types/functions/builtins/fns/GEBuiltin.h>
#include <APL/types/functions/builtins/fns/GTBuiltin.h>
#include <APL/types/functions/builtins/fns/NEBuiltin.h>
#include <APL/types/functions/builtins/mops/ReduceBuiltin.h>
#include <APL/types/functions/builtins/mops/ScanBuiltin.h>
#include <APL/types/functions/builtins/mops/EachBuiltin.h>
#include <APL/types/functions/builtins/mops/SelfieBuiltin.h>
#include <APL/types/functions/builtins/mops/KeyBuiltin.h>
#include <APL/types/functions/builtins/mops/ObliqueBuiltin.h>
#include <APL/types/functions/builtins/mops/EachLeft.h>
#include <APL/types/functions/builtins/mops/EachRight.h>
#include <APL/types/functions/builtins/dops/JotUBBuiltin.h>
#include <APL/types/functions/builtins/dops/RepeatBuiltin.h>
#include <APL/types/functions/builtins/dops/CRepeatBuiltin.h>
#include <APL/types/functions/builtins/dops/JotDiaeresisBuiltin.h>
#include <APL/types/functions/builtins/dops/OverBuiltin.h>
#include <APL/types/functions/builtins/dops/DualBuiltin.h>
#include <APL/types/functions/builtins/dops/AtBuiltin.h>
#include <APL/types/functions/builtins/dops/ObverseBuiltin.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/functions/builtins/Quad.h>
#include <APL/types/functions/builtins/QuoteQuad.h>
#include <APL/errors/NYIError.h>
#include <APL/tokenizer/types/NumTok.h>
#include <APL/tokenizer/types/ChrTok.h>
#include <APL/tokenizer/types/StrTok.h>
#include <APL/tokenizer/types/ParenTok.h>
#include <APL/types/StrMap.h>
#include <APL/types/arrs/Shape1Arr.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/functions/FunArr.h>
#include <APL/tokenizer/types/DfnTok.h>
#include <APL/tokenizer/types/BracketTok.h>
#include <APL/tokenizer/types/BacktickTok.h>
#include <APL/types/functions/ArrFun.h>
#include <APL/tokenizer/types/BigTok.h>
#include <APL/tokenizer/types/ScopeTok.h>

namespace APL
{
    // using namespace APL::errors;
    using Token = APL::tokenizer::Token;
    // using namespace APL::tokenizer::types;
    // using namespace APL::types;
    // using namespace APL::types::arrs;
    // using namespace APL::types::dimensions;
    // using namespace APL::types::functions;
    using AbstractSet = APL::types::functions::builtins::AbstractSet;
    // using namespace APL::types::functions::builtins;
    // using namespace APL::types::functions::builtins::dops;
    // using namespace APL::types::functions::builtins::fns;
    // using namespace APL::types::functions::builtins::mops;
    // using namespace APL::types::functions::trains;
    using UserDefined = APL::types::functions::userDefined::UserDefined;

    Exec::Exec(std::shared_ptr<APL::tokenizer::types::LineTok> ln, std::shared_ptr<Scope> sc) : sc(sc), tokens(ln->tokens), allToken(ln)
    {
    }

    void Exec::printlvl(std::vector<std::any> const& args)
    {
      if (!Main::debug)
      {
          return;
      }
      Main::printdbg(sc, std::vector<std::any> {Main::repeat(L"  ", Main::printlvl), args});
    }

    std::shared_ptr<APL::types::Obj> Exec::exec()
    {
      if (tokens.size() > 0)
      {
          Main::faulty = tokens[0];
      }
      else
      {
          Main::faulty = allToken;
      }
      if (sc->alphaDefined && tokens.size() >= 2 && std::dynamic_pointer_cast<OpTok>(tokens[0]) != nullptr && (std::static_pointer_cast<OpTok>(tokens[0]))->op == L"⍺" && std::dynamic_pointer_cast<SetTok>(tokens[1]) != nullptr)
      {
        if (Main::debug)
        {
            printlvl(std::vector<std::any> {L"skipping cuz it's ⍺←"});
        }
        return nullptr;
      }
      left = std::stack<Token>();
      left.addAll(tokens);
      if (Main::debug)
      {
        std::shared_ptr<StringBuilder> repr = std::make_shared<StringBuilder>();
        for (auto t : tokens)
        {
            repr->append(t->toRepr())->append(L" ");
        }
        printlvl(std::vector<std::any> {L"NEW:"});
        Main::printlvl++;
        printlvl(std::vector<std::any> {L"code:", repr});
        printlvl();
      }
      reset();
      std::vector<std::shared_ptr<APL::types::Obj>> arr;
      while (left.size() > 0)
      {
        std::shared_ptr<Token> t = left.pop();
        std::shared_ptr<APL::types::Obj> c;
        if (std::dynamic_pointer_cast<NameTok>(t) != nullptr && left.size() >= 2 && std::dynamic_pointer_cast<OpTok>(left.top()) != nullptr && (std::static_pointer_cast<OpTok>(left.top()))->op == L"." && std::dynamic_pointer_cast<NameTok>(left.get(left.size() - 2)) != nullptr)
        {
          int ptr = left.size() - 2;
          while (ptr >= 2)
          {
            if (std::dynamic_pointer_cast<OpTok>(left.get(ptr - 1)) != nullptr && (std::static_pointer_cast<OpTok>(left.get(ptr - 1)))->op == L"." && std::dynamic_pointer_cast<NameTok>(left.get(ptr - 2)) != nullptr)
            {
                ptr -= 2;
            }
            else
            {
                break;
            }
          }
          std::vector<std::string> names((left.size() - ptr >> 1) + 1);
          names[names.size() - 1] = (std::static_pointer_cast<NameTok>(t))->name;
          for (int i = names.size() - 2; i >= 0; i--)
          {
            std::shared_ptr<OpTok> dot = std::static_pointer_cast<OpTok>(left.pop());
            assert(dot->op == L".");
            std::shared_ptr<NameTok> name = std::static_pointer_cast<NameTok>(left.pop());
            names[i] = name->name;
          }

          if (Main::debug)
          {
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
              printlvl(std::vector<std::any> {L"dotnot", Arrays->toString(names)}); // todo fix (m).a (m).b0
          }
          std::shared_ptr<APL::types::Obj> d = nullptr;
          std::shared_ptr<Settable> r = sc->getVar(names[0]);
          for (int i = 1; i < names.size(); i++)
          {
            if (r == nullptr)
            {
              r = sc->getVar(names[i]);
              if (Main::debug)
              {
                  printlvl(std::vector<std::any> {L":start", d, r, names[i]});
              }
            }
            else
            {
              auto got = r->getOrThis();
              if (std::dynamic_pointer_cast<Fun>(got) != nullptr)
              {
                if (Main::debug)
                {
                    printlvl(std::vector<std::any> {L":fn", d, r, names[i]});
                }
                if (d == nullptr)
                {
                    d = got;
                }
                else
                {
                    d = (std::make_shared<DotBuiltin>())->derive(d, got);
                }
                r = sc->getVar(names[i]);
              }
              else if (std::dynamic_pointer_cast<APLMap>(got) != nullptr)
              {
                if (Main::debug)
                {
                    printlvl(std::vector<std::any> {L":map", d, r, names[i]});
                }
                r = (std::static_pointer_cast<APLMap>(got))[names[i]];
              }
              else
              {
                  throw SyntaxError(L"dot-chain contained non-fn/map");
              }
            }
          }
          if (r != nullptr)
          {
            if (d == nullptr)
            {
                d = r;
            }
            else
            {
                d = (std::make_shared<DotBuiltin>())->derive(d, r->get());
            }
          }
          else if (d == nullptr)
          {
              throw SyntaxError(L"what?");
          }
          c = d;
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {llToString()});
          }

        }
        else
        {
          c = valueOf(t);
        }
        if (c->isObj() || c->type() == Type::gettable && (left.empty() || !(std::dynamic_pointer_cast<SetTok>(left.get(0)) != nullptr)))
        {
          if (arr.empty())
          {
              arr = std::vector<APL::types::Obj>();
          }
          arr.push_back(c);
        }
        else
        {
          if (!arr.empty())
          {
            if (arr.size() == 1)
            {
                addS(arr[0]);
            }
            else
            {
                addS(VarArr::of(arr));
            }
            update(false);
            arr = std::vector<APL::types::Obj>();
          }
          addS(c);
          update(false);
        }
      }
      if (!arr.empty())
      {
        if (arr.size() == 1)
        {
            addS(arr[0]);
        }
        else
        {
            addS(VarArr::of(arr));
        }
      }
      update(true);


      Main::printlvl--;
      if (Main::debug)
      {
          printlvl(std::vector<std::any>
          {
              std::vector<std::any> {L"END:", llToString()}
          });
      }
      if (llSize != 1)
      {
        if (llSize == 0)
        {
            return nullptr;
        }
        if (pollS()->token != nullptr)
        {
            Main::faulty = pollS()->token;
        }
        // try to figure out what went wrong


        for (std::shared_ptr<Node> cn = LN->l; cn != FN; cn = cn->l)
        {
          std::shared_ptr<APL::types::Obj> obj = cn->val;
          if (std::dynamic_pointer_cast<Variable>(obj) != nullptr)
          {
            std::shared_ptr<Variable> vobj = std::static_pointer_cast<Variable>(obj);
            if (vobj->getOrThis() == obj)
            {
                throw SyntaxError(StringHelper::wstring_to_string(L"Couldn't find the value of " + vobj->name, obj));
            }
          }
          else if (std::dynamic_pointer_cast<Settable>(obj) != nullptr)
          {
            std::shared_ptr<Settable> settable = std::static_pointer_cast<Settable>(obj);
            if (settable->getOrThis() == obj)
            {
                throw SyntaxError(StringHelper::wstring_to_string(L"Couldn't find the value of " + obj, obj));
            }
          }
        }

        // oh well that failed
        throw SyntaxError(L"Failed to parse expression", pollL());
      }
      return pollS();
    }

    void Exec::update(bool end)
    {
      if (llSize == 1 && pollS() == nullptr)
      {
          return;
      }
      while (llSize != 1)
      {
        if (Main::debug)
        {
            printlvl(std::vector<std::any> {llToString()});
        }
        if (is(L"D!|NFN", end, false))
        {
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {L"NFN"});
          }
          auto w = lastVal();
          auto f = lastFun();
          auto a = lastVal();
          Main::faulty = f;
          auto res = f->callObj(a, w);
          if (res == nullptr && (left.size() > 0 || llSize > 0))
          {
              throw SyntaxError(L"trying to use result of function which returned nothing", a);
          }
          if (res != nullptr)
          {
              addE(res);
          }
          else
          {
              return;
          }
          continue;
        }
        if (llSize >= 2 && FN->r->r->type == L'@')
        {
          if (is(L"F@", end, true))
          {
            if (Main::debug)
            {
                printlvl(std::vector<std::any> {L"F[]"});
            }
            auto f = std::static_pointer_cast<Fun>(firstObj());
            auto w = std::static_pointer_cast<Brackets>(popS());
            addS(std::make_shared<DervDimFn>(f, w->toInts(), sc));
            continue;
          }
          if (is(L"M@", end, true))
          {
            if (Main::debug)
            {
                printlvl(std::vector<std::any> {L"M[]"});
            }
            auto f = firstMop();
            auto w = std::static_pointer_cast<Brackets>(popS());
            addS(std::make_shared<DervDimMop>(f, w->toInt(), sc));
            continue;
          }
          if (is(L"D@", end, true))
          {
            if (Main::debug)
            {
                printlvl(std::vector<std::any> {L"D[]"});
            }
            auto f = firstDop();
            auto w = std::static_pointer_cast<Brackets>(popS());
            addS(std::make_shared<DervDimDop>(f, w->toInt(), sc));
            continue;
          }
          if (is(L"v@", end, true))
          {
            if (Main::debug)
            {
                printlvl(std::vector<std::any> {L"v[]"});
            }
            auto f = firstVar();
            auto w = std::static_pointer_cast<Brackets>(popS());
            addS(std::make_shared<Pick>(std::static_pointer_cast<Variable>(f), w, sc));
            continue;
          }
          if (is(L"N@", end, true))
          {
            if (Main::debug)
            {
                printlvl(std::vector<std::any> {L"n[]"});
            }
            auto a = firstVal();
            auto w = std::static_pointer_cast<Brackets>(popS());
            addS(RShoeUBBuiltin::on(w->val, a, sc->IO, w));
            continue;
          }
        }
        if (is(L"[FM←]|FN", end, false))
        {
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {L"FN"});
          }
          auto w = lastVal();
          auto f = lastFun();
          Main::faulty = f;
          auto res = f->callObj(w);
          if (res == nullptr && (left.size() > 0 || llSize > 0))
          {
              throw SyntaxError(L"trying to use result of function which returned nothing", f);
          }
          if (res != nullptr)
          {
              addE(res);
          }
          else
          {
              return;
          }
          continue;
        }
        if (is(L"#!←", end, true) || llSize == 1 && pollS()->type() == Type::gettable)
        {
          auto w = firstVar();
          addFirst(w->get());
        }

        if (llSize > 2 && LN->l->l->type == L'←')
        {
          if (is(std::vector<std::string>{L"D!|V←[#NFMD]", L"#←[#NFMDV]", L"D!|D←D", L"D!|M←M", L"D!|F←F", L"D!|N←N"}, end, false))
          { // "D!|.←." to allow changing type
            if (Main::debug)
            {
                printlvl(std::vector<std::any> {L"N←."});
            }
            auto w = lastObj();
            auto s = std::static_pointer_cast<AbstractSet>(popE()); // ←
            auto a = popE(); // variable
            Main::faulty = s;
            auto res = s->callObj(a, w, false);
            addE(res);
            continue;
          }
          if (is(L"D!|NF←N", end, false, 5))
          {
            if (Main::debug)
            {
                printlvl(std::vector<std::any> {L"NF←."});
            }
            auto w = lastVal();
            auto s0 = popE(); // ←
            if (std::dynamic_pointer_cast<DerivedSet>(s0) != nullptr)
            {
                throw SyntaxError(L"cannot derive an already derived ←");
            }
            auto s = std::static_pointer_cast<APL::types::functions::builtins::SetBuiltin>(s0);
            auto f = lastFun();
            std::shared_ptr<APL::types::Obj> a = popE(); // variable
            Main::faulty = f;
            std::shared_ptr<APL::types::Obj> res = s->callObj(f, a, w);
            if (res != nullptr)
            {
                addE(res);
            }
            continue;
          }
        }

        if (llSize == 2 && is(L"F←", false, false))
        {
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {L"F←"});
          }
          auto s0 = popE(); // ←
          if (std::dynamic_pointer_cast<DerivedSet>(s0) != nullptr)
          {
              throw SyntaxError(L"cannot derive an already derived ←");
          }
          auto s = std::static_pointer_cast<APL::types::functions::builtins::SetBuiltin>(s0);
          auto f = lastFun();
          addE(std::make_shared<DerivedSet>(s, f));
          continue;
        }

        if (is(L"!D|[FN]M", end, true))
        {
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {L"FM"});
          }
          auto f = firstObj();
          auto o = firstMop();
          addFirst(o->derive(f));
          continue;
        }
        if (is(L"!D|[FNV]D[FNV]", end, true))
        {
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {L"FDF"});
          }
          auto aa = popB(); // done.removeFirst();
          auto o = firstDop(); // (Dop) done.removeFirst();
          auto ww = popB();
          auto aau = aa;
          auto wwu = ww;
          if (std::dynamic_pointer_cast<Settable>(aau) != nullptr)
          {
              aau = (std::static_pointer_cast<Settable>(aau))->getOrThis();
          }
          if (std::dynamic_pointer_cast<Settable>(wwu) != nullptr)
          {
              wwu = (std::static_pointer_cast<Settable>(wwu))->getOrThis();
          }
          if (std::dynamic_pointer_cast<VarArr>(aau) != nullptr)
          {
              aau = (std::static_pointer_cast<VarArr>(aau))->get();
          }
          if (std::dynamic_pointer_cast<VarArr>(wwu) != nullptr)
          {
              wwu = (std::static_pointer_cast<VarArr>(wwu))->get();
          }
          if (std::dynamic_pointer_cast<DotBuiltin>(o) != nullptr && std::dynamic_pointer_cast<APLMap>(aau) != nullptr && std::dynamic_pointer_cast<Variable>(ww) != nullptr)
          {
            addB((std::static_pointer_cast<APLMap>(aau))[Main::toAPL((std::static_pointer_cast<Variable>(ww))->name)]);
          }
          else
          {
            addB(o->derive(aau, wwu));
          }
          continue;
        }
        if (is(L"D!|[FN]FF", end, false))
        {
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {L"f g h"});
          }
          auto h = lastFun();
          auto g = lastFun();
          auto f = lastObj();
          addE(std::make_shared<Fork>(f, g, h));
          continue;
        }
        if (is(L"D!|NF", false, false))
        {
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {L"A f"});
          }
          auto f = lastFun();
          auto a = lastObj();
          addE(std::make_shared<Atop>(a, f));
          continue;
        }
        if (is(L"←FF", false, false))
        {
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {L"g h"});
          }
          auto h = lastFun();
          auto g = lastObj();
          addE(std::make_shared<Atop>(g, h));
          continue;
        }
        if (llSize >= 3 && std::dynamic_pointer_cast<JotBuiltin>(pollS()) != nullptr && std::dynamic_pointer_cast<DotBuiltin>(FN->r->r->val) != nullptr)
        {
          if (Main::debug)
          {
              printlvl(std::vector<std::any> {L"∘."});
          }
          auto jot = popS();
          popS();
          auto fn = popS();
          if (std::dynamic_pointer_cast<Settable>(fn) != nullptr)
          {
              fn = (std::static_pointer_cast<Settable>(fn))->get();
          }
          if (std::dynamic_pointer_cast<VarArr>(fn) != nullptr)
          {
              fn = (std::static_pointer_cast<VarArr>(fn))->get();
          }
          auto TB = std::make_shared<TableBuiltin>();
          TB->token = jot->token;
          addS(TB->derive(fn));
          continue;
        }
        break;
      }
      if (end && llSize == 2)
      {
        if (Main::debug)
        {
            printlvl(std::vector<std::any> {L"g h"});
        }
        auto h = lastFun();
        auto g = lastObj();
        if (std::dynamic_pointer_cast<Fun>(g) != nullptr || std::dynamic_pointer_cast<APL::types::Value>(g) != nullptr)
        {
            addE(std::make_shared<Atop>(g, h));
        }
        else
        {
            throw SyntaxError(StringHelper::wstring_to_string(L"creating an atop with " + g->humanType(true), g));
        }
      }
    }

    std::shared_ptr<APL::types::Value> Exec::lastVal()
    {
      auto r = popE();
      if (std::dynamic_pointer_cast<Settable>(r) != nullptr)
      {
          r = (std::static_pointer_cast<Settable>(r))->get();
      }
      if (std::dynamic_pointer_cast<APL::types::Value>(r) != nullptr)
      {
          return std::static_pointer_cast<APL::types::Value>(r);
      }
      if (std::dynamic_pointer_cast<VarArr>(r) != nullptr)
      {
          return (std::static_pointer_cast<VarArr>(r))->get();
      }
      throw SyntaxError(StringHelper::wstring_to_string(L"Expected value, got " + r, r));
    }

    std::shared_ptr<Fun> Exec::lastFun()
    {
      auto r = popE();
      if (std::dynamic_pointer_cast<Settable>(r) != nullptr)
      {
          r = (std::static_pointer_cast<Settable>(r))->get();
      }
      if (std::dynamic_pointer_cast<Fun>(r) != nullptr)
      {
          return std::static_pointer_cast<Fun>(r);
      }
      throw SyntaxError(StringHelper::wstring_to_string(L"Expected function, got " + r, r));
    }

    std::shared_ptr<APL::types::Value> Exec::firstVal()
    {
      auto r = popB();
      if (std::dynamic_pointer_cast<Settable>(r) != nullptr)
      {
          r = (std::static_pointer_cast<Settable>(r))->get();
      }
      if (std::dynamic_pointer_cast<APL::types::Value>(r) != nullptr)
      {
          return std::static_pointer_cast<APL::types::Value>(r);
      }
      if (std::dynamic_pointer_cast<VarArr>(r) != nullptr)
      {
          return (std::static_pointer_cast<VarArr>(r))->get();
      }
      throw SyntaxError(StringHelper::wstring_to_string(L"Expected value, got " + r, r));
    }

    std::shared_ptr<Dop> Exec::firstDop()
    {
      auto r = popB();
      if (std::dynamic_pointer_cast<Settable>(r) != nullptr)
      {
          r = (std::static_pointer_cast<Settable>(r))->get();
      }
      if (std::dynamic_pointer_cast<Dop>(r) != nullptr)
      {
          return std::static_pointer_cast<Dop>(r);
      }
      throw SyntaxError(StringHelper::wstring_to_string(L"Expected dop, got " + r, r));
    }

    std::shared_ptr<APL::types::Obj> Exec::lastObj()
    {
      auto r = popE();
      if (std::dynamic_pointer_cast<Settable>(r) != nullptr)
      {
          r = (std::static_pointer_cast<Settable>(r))->get();
      }
      if (std::dynamic_pointer_cast<VarArr>(r) != nullptr)
      {
          return (std::static_pointer_cast<VarArr>(r))->get();
      }
      return r;
    }

    std::shared_ptr<APL::types::Obj> Exec::firstObj()
    {
      auto r = popB();
      if (std::dynamic_pointer_cast<VarArr>(r) != nullptr)
      {
          return (std::static_pointer_cast<VarArr>(r))->get();
      }
      if (std::dynamic_pointer_cast<Settable>(r) != nullptr)
      {
          return (std::static_pointer_cast<Settable>(r))->get();
      }
      return r;
    }

    std::shared_ptr<Settable> Exec::firstVar()
    {
      auto r = popB();
      if (std::dynamic_pointer_cast<Settable>(r) != nullptr)
      {
          return std::static_pointer_cast<Settable>(r);
      }
      throw SyntaxError(StringHelper::wstring_to_string(L"Expected a variable, got " + r, r));
    }

    std::shared_ptr<Mop> Exec::firstMop()
    {
      auto r = popB();
      if (std::dynamic_pointer_cast<Settable>(r) != nullptr)
      {
          r = (std::static_pointer_cast<Settable>(r))->get();
      }
      if (std::dynamic_pointer_cast<Mop>(r) != nullptr)
      {
          return std::static_pointer_cast<Mop>(r);
      }
      throw SyntaxError(StringHelper::wstring_to_string(L"Expected mop, got " + r, r));
    }

    void Exec::addFirst(std::shared_ptr<APL::types::Obj> o)
    {
      addB(o);
    }

    std::shared_ptr<APL::types::Obj> Exec::popS()
    {
      llSize--;
      std::shared_ptr<Node> c = FN->r;
      std::shared_ptr<Node> r = c->r;
      std::shared_ptr<APL::types::Obj> res = c->val;
      FN->r = c->r;
      r->l = FN;
      return res;
    }

    std::shared_ptr<APL::types::Obj> Exec::popE()
    {
      llSize--;
      std::shared_ptr<Node> c = LN->l;
      std::shared_ptr<Node> l = c->l;
      std::shared_ptr<APL::types::Obj> r = c->val;
      LN->l = c->l;
      l->r = LN;
      return r;
    }

    std::shared_ptr<APL::types::Obj> Exec::popB()
    {
      llSize--;
      std::shared_ptr<APL::types::Obj> r = barNode->remove();
      barNode = barNode->r;
      return r;
    }

    void Exec::addS(std::shared_ptr<APL::types::Obj> o)
    {
      llSize++;
      std::shared_ptr<Node> r = FN->r;
      std::shared_ptr<Node> l = FN->r->l;
      assert(l == FN);
      std::shared_ptr<Node> n = std::make_shared<Node>(o, l, r);
      l->r = n;
      r->l = n;
    }

    void Exec::addE(std::shared_ptr<APL::types::Obj> o)
    {
      llSize++;
      std::shared_ptr<Node> l = LN->l;
      std::shared_ptr<Node> r = LN->l->r;
      assert((r == LN, llToString()));
      std::shared_ptr<Node> n = std::make_shared<Node>(o, l, r);
      l->r = n;
      r->l = n;
    }

    void Exec::addB(std::shared_ptr<APL::types::Obj> o)
    {
      llSize++;
      std::shared_ptr<Node> l = barNode->l;
      std::shared_ptr<Node> r = barNode;
      std::shared_ptr<Node> n = std::make_shared<Node>(o, l, r);
      l->r = n;
      r->l = n;
      barNode = n;
    }

    std::shared_ptr<APL::types::Obj> Exec::pollS()
    {
      return FN->r->val;
    }

    std::shared_ptr<APL::types::Obj> Exec::pollL()
    {
      return LN->l->val;
    }

    void Exec::reset()
    {
      FN = std::make_shared<Node>();
      LN = std::make_shared<Node>();
      FN->r = LN;
      LN->l = FN;
      FN->l = LN->r = nullptr;
    }

    Exec::Node::Node()
    {
    }

    Exec::Node::Node(std::shared_ptr<APL::types::Obj> val, std::shared_ptr<Node> l, std::shared_ptr<Node> r)
    {
      this->l = l;
      this->r = r;
      this->val = val;
      type = val->type().chr;
    }

    std::shared_ptr<APL::types::Obj> Exec::Node::remove()
    {
      l->r = r;
      r->l = l;
      return val;
    }

    std::string Exec::Node::toString()
    {
      // return hashCode()+"{"+l.hashCode()+"; "+r.hashCode()+"}\n";
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
      return val == nullptr? L"null" : val->toString();
    }

    std::string Exec::llToString()
    {
      std::shared_ptr<StringBuilder> r = std::make_shared<StringBuilder>(L"[");
      std::shared_ptr<Node> c = FN->r;
      bool first = true;
      while (c != LN)
      {
        if (first)
        {
            first = false;
        }
        else
        {
            r->append(L", ");
        }
        r->append(c);
        c = c->r;
      }
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
      return r->append(L"]")->toString();
    }

    bool Exec::is(std::vector<std::string> &pts, bool everythingDone, bool fromStart)
    {
      for (auto pt : pts)
      {
          if (is(pt, everythingDone, fromStart))
          {
              return true;
          }
      }
      return false;
    }

    bool Exec::is(std::string const& pt, bool everythingDone, bool fromStart)
    {
      return is(pt, everythingDone, fromStart, 4);
    }

    bool Exec::is(std::string const& pt, bool everythingDone, bool fromStart, int am)
    {
      if (!fromStart && llSize > am)
      {
          return false;
      }
      if (everythingDone && is(pt, false, fromStart))
      {
          return true;
      }
      if (fromStart && everythingDone)
      {
        for (int i = 0; i < pt.length(); i++)
        {
          if (pt[i] == L'|')
          {
              return is(pt.substr(i + 1), false, true);
          }
        }
      }
      int len = pt.length();
      int ptrinc = fromStart ? 1 : -1;
      bool pass = false;
      barNode = FN->r;
      std::shared_ptr<Node> cn = fromStart? FN->r : LN->l;
      for (int i = fromStart ? 0 : len - 1; fromStart ? i<len : std::shared_ptr<i >>= 0; i += ptrinc)
      {
        wchar_t p = pt[i];
        bool inv = false;
        if (p == L'|')
        {
          pass = everythingDone;
          barNode = cn;
          i += ptrinc;
          p = pt[i];
        }
        if (cn == FN | cn == LN)
        {
            return pass;
        }
        if (p == L'!')
        {
          inv = true;
          i += ptrinc;
          p = pt[i];
        }
        std::shared_ptr<APL::types::Obj> v = cn->val;
        if (p == L'v')
        {
          if (!(std::dynamic_pointer_cast<Settable>(v) != nullptr) ^ inv)
          {
              return false;
          }
          cn = fromStart? cn->r : cn->l;
          continue;
        }
        if (p == L'.')
        {
          cn = fromStart? cn->r : cn->l;
          continue;
        }

        wchar_t type = cn->type;
        if (p == L']')
        { // regular guaranteed
          i--;
          bool nf = true;
          while (true)
          {
            wchar_t c = pt[i];
            if (c == L'[')
            {
                break;
            }
            if (c == type)
            {
                nf = false;
            }
            i--;
          }
          if (nf)
          {
              return false; // no inv for []s!
          }
        }
        else if (p == L'[')
        { // reverse guaranteed
          i++;
          bool nf = true;
          while (true)
          {
            wchar_t c = pt[i];
            if (c == L']')
            {
                break;
            }
            if (c == type)
            {
                nf = false;
            }
            i++;
          }
          if (nf)
          {
              return false;
          }
        }
        else
        {
          if (p != type ^ inv)
          {
              return false;
          }
        }
        cn = fromStart? cn->r : cn->l;
      }
      return true;
    }

    std::shared_ptr<APL::types::Obj> Exec::valueOf(std::shared_ptr<Token> t)
    {
      std::shared_ptr<APL::types::Obj> o = valueOfRaw(t);
      o->token = t;
      return o;
    }

    std::shared_ptr<APL::types::Obj> Exec::valueOfRaw(std::shared_ptr<Token> t)
    {
      if (std::dynamic_pointer_cast<OpTok>(t) != nullptr)
      {
        std::shared_ptr<OpTok> t1 = std::static_pointer_cast<OpTok>(t);
        switch (t1->op[0])
        {
          // slashes: / - reduce; ⌿ - replicate; \ - reduce (r[3]←(r[2] ← (r[1]←a) f b) f c); ⍀ - extend
          // in Dyalog but not at least partially implemented: ⊆⌹→  &⌶⌺
          // fns
          case L'+':
              return std::make_shared<PlusBuiltin>();
          case L'-':
              return std::make_shared<MinusBuiltin>();
          case L'×':
              return std::make_shared<MulBuiltin>();
          case L'÷':
              return std::make_shared<DivBuiltin>();
          case L'*':
              return std::make_shared<StarBuiltin>();
          case L'⍟':
              return std::make_shared<LogBuiltin>();
          case L'√':
              return std::make_shared<RootBuiltin>();
          case L'⌈':
              return std::make_shared<CeilingBuiltin>();
          case L'⌊':
              return std::make_shared<FloorBuiltin>();
          case L'|':
              return std::make_shared<StileBuiltin>();
          case L'∧':
              return std::make_shared<AndBuiltin>();
          case L'∨':
              return std::make_shared<OrBuiltin>();
          case L'⍲':
              return std::make_shared<NandBuiltin>(sc);
          case L'⍱':
              return std::make_shared<NorBuiltin>(sc);
          case L'⊥':
              return std::make_shared<UTackBuiltin>();
          case L'⊤':
              return std::make_shared<DTackBuiltin>();
          case L'~':
              return std::make_shared<TildeBuiltin>();
          case L'○':
              return std::make_shared<TrigBuiltin>();
          case L'!':
              return std::make_shared<ExclBuiltin>();

          case L'∊':
              return std::make_shared<EpsilonBuiltin>();
          case L'⍷':
              return std::make_shared<FindBuiltin>();
          case L'⊂':
              return std::make_shared<LShoeBuiltin>();
          case L'⊇':
              return std::make_shared<RShoeUBBuiltin>(sc);
          case L'⊃':
              return std::make_shared<RShoeBuiltin>(sc);
          case L'∪':
              return std::make_shared<DShoeBuiltin>();
          case L'∩':
              return std::make_shared<UShoeBuiltin>();
          case L'⌷':
              return std::make_shared<SquadBuiltin>(sc);
          case L'⍳':
              return std::make_shared<IotaBuiltin>(sc);
          case L'⍸':
              return std::make_shared<IotaUBBuiltin>(sc);
          case L'⍴':
              return std::make_shared<RhoBuiltin>();
          case L',':
              return std::make_shared<CatBuiltin>();
          case L'≢':
              return std::make_shared<TallyBuiltin>();
          case L'≡':
              return std::make_shared<DepthBuiltin>();
          case L'⊢':
              return std::make_shared<RTackBuiltin>();
          case L'⊣':
              return std::make_shared<LTackBuiltin>();
          case L'↑':
              return std::make_shared<UpArrowBuiltin>();
          case L'↓':
              return std::make_shared<DownArrowBuiltin>();
          case L'?':
              return std::make_shared<RandBuiltin>(sc);
          case L'⍪':
              return std::make_shared<CommaBarBuiltin>();
          case L'⍉':
              return std::make_shared<TransposeBuiltin>();
          case L'⊖':
              return std::make_shared<FlipBuiltin>();
          case L'⌽':
              return std::make_shared<ReverseBuiltin>();

          case L'…':
              return std::make_shared<EllipsisBuiltin>();
          case L'⍮':
              return std::make_shared<SemiUBBuiltin>();
          case L'⍕':
              return std::make_shared<FormatBuiltin>();
          case L'⍎':
              return std::make_shared<EvalBuiltin>(sc);
          case L'⍋':
              return std::make_shared<GradeUpBuiltin>(sc);
          case L'⍒':
              return std::make_shared<GradeDownBuiltin>(sc);
          case L'⌿':
              return std::make_shared<ReplicateBuiltin>();
          case L'⍀':
              return std::make_shared<ExpandBuiltin>();
          case L'⍧':
              return std::make_shared<LShoeStileBuiltin>();
          case L'%':
              return std::make_shared<MergeBuiltin>(sc);

          // comparisons
          case L'<':
              return std::make_shared<LTBuiltin>();
          case L'≤':
              return std::make_shared<LEBuiltin>();
          case L'=':
              return std::make_shared<EQBuiltin>();
          case L'≥':
              return std::make_shared<GEBuiltin>();
          case L'>':
              return std::make_shared<GTBuiltin>();
          case L'≠':
              return std::make_shared<NEBuiltin>();

          // mops
          case L'/':
              return std::make_shared<ReduceBuiltin>();
          case L'\\':
              return std::make_shared<ScanBuiltin>();
          case L'¨':
              return std::make_shared<EachBuiltin>();
          case L'⍨':
              return std::make_shared<SelfieBuiltin>();
          case L'⌾':
              return std::make_shared<TableBuiltin>();
          case L'⌸':
              return std::make_shared<KeyBuiltin>(sc);
          case L'⍁':
              return std::make_shared<ObliqueBuiltin>();
          case L'⍩':
          case L'ᐵ':
              return std::make_shared<EachLeft>();
          case L'ᑈ':
              return std::make_shared<EachRight>();

          // dops
          case L'∘':
              return std::make_shared<JotBuiltin>();
          case L'⍛':
              return std::make_shared<JotUBBuiltin>();
          case L'.':
              return std::make_shared<DotBuiltin>();
          case L'⍣':
              return std::make_shared<RepeatBuiltin>(sc);
          case L'⍡':
              return std::make_shared<CRepeatBuiltin>(sc);
          case L'⍤':
              return std::make_shared<JotDiaeresisBuiltin>();
          case L'⍥':
              return std::make_shared<OverBuiltin>();
          case L'⍢':
              return std::make_shared<DualBuiltin>();
          case L'@':
              return std::make_shared<AtBuiltin>(sc);
          case L'⍫':
              return std::make_shared<ObverseBuiltin>();


          case L'⍬':
              return std::make_shared<DoubleArr>(DoubleArr::EMPTY);
          case L'⎕':
              return std::make_shared<Quad>(sc);
          case L'⍞':
              return std::make_shared<QuoteQuad>(sc);
          case L'⍺':
          {
              std::shared_ptr<APL::types::Obj> o = sc->get(L"⍺");
              if (o == nullptr)
              {
                  throw SyntaxError(L"No ⍺ found", t);
              }
              return o;
          }
          case L'⍵':
              o = sc->get(L"⍵");
              if (o == nullptr)
              {
                  throw SyntaxError(L"No ⍵ found", t);
              }
              return o;
          case L'∇':
              o = sc->get(L"∇");
              if (o == nullptr)
              {
                  throw SyntaxError(L"No ∇ found", t);
              }
              return o;
          case L'⍶':
              o = sc->get(L"⍶");
              if (o == nullptr)
              {
                  throw SyntaxError(L"No ⍶ found", t);
              }
              return o;
          case L'⍹':
              o = sc->get(L"⍹");
              if (o == nullptr)
              {
                  throw SyntaxError(L"No ⍹ found", t);
              }
              return o;
          default:
              throw APL::errors::NYIError(StringHelper::wstring_to_string(L"no built-in " + (std::static_pointer_cast<OpTok>(t))->op + L" defined in exec", t));
        }
      }
      if (std::dynamic_pointer_cast<NumTok>(t) != nullptr)
      {
          return (std::static_pointer_cast<NumTok>(t))->num;
      }
      if (std::dynamic_pointer_cast<ChrTok>(t) != nullptr)
      {
          return (std::static_pointer_cast<ChrTok>(t))->val;
      }
      if (std::dynamic_pointer_cast<StrTok>(t) != nullptr)
      {
          return (std::static_pointer_cast<StrTok>(t))->val;
      }
      if (std::dynamic_pointer_cast<SetTok>(t) != nullptr)
      {
          return SetBuiltin::inst;
      }
      if (std::dynamic_pointer_cast<NameTok>(t) != nullptr)
      {
          return sc->getVar((std::static_pointer_cast<NameTok>(t))->name);
      }
      if (std::dynamic_pointer_cast<APL::tokenizer::types::LineTok>(t) != nullptr)
      {
          return Main::rexec(std::static_pointer_cast<APL::tokenizer::types::LineTok>(t), sc);
      }
      if (std::dynamic_pointer_cast<ParenTok>(t) != nullptr)
      {
        std::vector<std::shared_ptr<APL::tokenizer::types::LineTok>> ts = (std::static_pointer_cast<ParenTok>(t))->tokens;
        int size = ts.size();
        if (size == 0)
        {
            return std::make_shared<StrMap>();
        }
        std::shared_ptr<APL::tokenizer::types::LineTok> fst = ts[0];
        if (size == 1 && fst->colonPos() == -1)
        {
          if ((std::static_pointer_cast<ParenTok>(t))->hasDmd)
          {
              return std::make_shared<Shape1Arr>(Main::vexec(ts[0], sc));
          }
          return Main::rexec(ts[0], sc);
        }
        if (fst->tokens != nullptr && fst->colonPos() != -1)
        { // map constants
          std::shared_ptr<Scope> nsc = std::make_shared<Scope>(sc);
          std::shared_ptr<StrMap> res = std::make_shared<StrMap>(nsc);
          for (auto ct : ts)
          {
            std::shared_ptr<Token> name = ct->tokens->get(0);
            if (ct->colonPos() == -1)
            {
                throw SyntaxError(L"expected a colon in expression", ct->tokens->get(0));
            }
            if (ct->colonPos() != 1)
            {
                throw SyntaxError(L"expected : to be the 2nd token in parenthesis", ct->tokens->get(ct->colonPos()));
            }
            std::string key;
            if (std::dynamic_pointer_cast<NameTok>(name) != nullptr)
            {
                key = (std::static_pointer_cast<NameTok>(name))->name;
            }
            else if (std::dynamic_pointer_cast<StrTok>(name) != nullptr)
            {
                key = (std::static_pointer_cast<StrTok>(name))->parsed;
            }
            else if (std::dynamic_pointer_cast<ChrTok>(name) != nullptr)
            {
                key = (std::static_pointer_cast<ChrTok>(name))->parsed;
            }
            else
            {
                throw SyntaxError(StringHelper::wstring_to_string(L"expected a key name, got " + name->toRepr(), name));
            }
            std::vector<std::shared_ptr<Token>> tokens = ct->tokens.subList(2, ct->tokens->size());

            std::shared_ptr<APL::types::Obj> val = Main::exec(APL::tokenizer::types::LineTok::inherit(tokens), nsc);
            res->setStr(key, val);
          }
          return res;
        }
        else
        { // array
          std::shared_ptr<APL::types::Obj> fo = Main::exec(fst, sc);
          if (std::dynamic_pointer_cast<APL::types::Value>(fo) != nullptr)
          { // value array
            std::vector<std::shared_ptr<APL::types::Value>> vs(size);
            for (int i = 0; i < ts.size(); i++)
            {
              std::shared_ptr<APL::types::Obj> o = i == 0? fo : Main::exec(ts[i], sc);
              if (!(std::dynamic_pointer_cast<APL::types::Value>(o) != nullptr))
              {
                  throw DomainError(StringHelper::wstring_to_string(L"⋄-array contained " + o->humanType(true), o));
              }
              vs[i] = std::static_pointer_cast<APL::types::Value>(o);
            }
            return Arr::create(vs);
          }
          else if (std::dynamic_pointer_cast<Fun>(fo) != nullptr)
          { // function array
            std::vector<std::shared_ptr<APL::types::Obj>> os(size);
            for (int i = 0; i < ts.size(); i++)
            {
              std::shared_ptr<APL::types::Obj> o = i == 0? fo : Main::exec(ts[i], sc);
              if (!(std::dynamic_pointer_cast<Fun>(o) != nullptr))
              {
                  throw DomainError(StringHelper::wstring_to_string(L"function array contained " + o->humanType(true), o));
              }
              os[i] = o;
            }
            return std::make_shared<FunArr>(os);
          }
          else
          {
              throw DomainError(StringHelper::wstring_to_string(L"⋄-array contained " + fo->humanType(true), fo));
          }
        }
      }
      if (std::dynamic_pointer_cast<DfnTok>(t) != nullptr)
      {
          return UserDefined::of(std::static_pointer_cast<DfnTok>(t), sc);
      }
      if (std::dynamic_pointer_cast<APL::tokenizer::types::BracketTok>(t) != nullptr)
      {
          return Brackets::of(std::static_pointer_cast<APL::tokenizer::types::BracketTok>(t), sc);
      }
      if (std::dynamic_pointer_cast<BacktickTok>(t) != nullptr)
      {
          return std::make_shared<ArrFun>(std::static_pointer_cast<BacktickTok>(t), sc);
      }
      if (std::dynamic_pointer_cast<BigTok>(t) != nullptr)
      {
          return (std::static_pointer_cast<BigTok>(t))->val;
      }
      if (std::dynamic_pointer_cast<ScopeTok>(t) != nullptr)
      {
          return std::make_shared<StrMap>(sc);
      }
      throw APL::errors::NYIError(StringHelper::wstring_to_string(L"Unknown type: " + t->toRepr(), t));
    }
}
