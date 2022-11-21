#include <APL/types/Char.h>
#include <APL/types/Arr.h>

namespace APL::types
{
    // using Main = APL::Main;
    // using ChrArr = APL::types::arrs::ChrArr;
std::vector<std::shared_ptr<Char>> Char::ASCII;

    Char::StaticConstructor::StaticConstructor()
    {
                ASCII = std::vector<std::shared_ptr<Char>>(128);
                for (int i = 0; i < 128; i++)
                {
    ASCII[i] = std::make_shared<Char>(static_cast<wchar_t>(i));
                }
    }

Char::StaticConstructor Char::staticConstructor;
const std::shared_ptr<Char> Char::SPACE = ASCII[L' '];

    Char::Char(wchar_t c)
    {
      chr = c;
    }

    std::shared_ptr<Char> Char::of(wchar_t c)
    {
      if (c < 128)
      {
          return ASCII[c];
      }
      return std::make_shared<Char>(c);
    }

    std::shared_ptr<Char> Char::upper()
    {
      return Char::of(std::toupper(chr));
    }

    std::shared_ptr<Char> Char::lower()
    {
      return Char::of(std::tolower(chr));
    }

    std::shared_ptr<Char> Char::swap()
    {
      if (std::isupper(chr))
      {
          return lower();
      }
      if (std::islower(chr))
      {
          return upper();
      }
      return Char::of(chr);
    }

    int Char::getCase()
    {
      return std::isupper(chr)? 1 : std::islower(chr)? -1 : 0;
    }

    std::string Char::toString()
    {
      if (Main::quotestrings)
      {
          return L"'" + StringHelper::toString(chr) + L"'";
      }
      else
      {
          return StringHelper::toString(chr);
      }
    }

    std::string Char::oneliner(std::vector<int> &ignored)
    {
      return L"'" + StringHelper::toString(chr) + L"'";
    }

    std::shared_ptr<APL::types::Value> Char::ofShape(std::vector<int> &sh)
    {
      if (sh.empty() && !Main::enclosePrimitives)
      {
          return shared_from_this();
      }
      assert(ia == Arr::prod(sh));
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
      return std::make_shared<APL::types::arrs::ChrArr>(Character::toString(chr), sh); // special because there's no quickCharArr
    }

    int Char::compareTo(std::shared_ptr<Char> v)
    {
      return Character::compare(chr, v->chr);
    }

    bool Char::equals(std::shared_ptr<APL::types::Obj> c)
    {
      return std::dynamic_pointer_cast<Char>(c) != nullptr && chr == (std::static_pointer_cast<Char>(c))->chr;
    }

    std::string Char::asString()
    {
      return StringHelper::toString(chr);
    }

    int Char::hashCode()
    {
      return chr;
    }

    std::shared_ptr<APL::types::Value> Char::safePrototype()
    {
      return SPACE;
    }
}
