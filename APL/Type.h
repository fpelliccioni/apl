#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <utility>

namespace APL
{

    enum class Type
    {
      array = L'N',
      var = L'V',
      nul = L'V',
      gettable = L'#',
      fn = L'F',
      mop = L'M',
      dop = L'D',
      set = L'←',
      dim = L'@'

//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//      public final char chr;

//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//      Type(char chr)
    //  {
    //    this.chr = chr;
    //  }
    };

    class TypeHelper
    {
    private:
        static std::vector<std::pair<Type, std::string>> pairs()
        {
            return
            {
                {Type::array, L"array"},
                {Type::var, L"var"},
                {Type::nul, L"nul"},
                {Type::gettable, L"gettable"},
                {Type::fn, L"fn"},
                {Type::mop, L"mop"},
                {Type::dop, L"dop"},
                {Type::set, L"set"},
                {Type::dim, L"dim"}
            };
        }

    public:
        static std::vector<Type> values()
        {
            std::vector<Type> temp;
            for (auto pair : pairs())
            {
                temp.push_back(pair.first);
            }
            return temp;
        }

        static std::string enumName(Type value)
        {
            for (auto pair : pairs())
            {
                if (pair.first == value)
                    return pair.second;
            }

            throw std::runtime_error("Enum not found.");
        }

        static int ordinal(Type value)
        {
            std::vector<std::pair<Type, std::string>> temp = pairs();
            for (std::size_t i = 0; i < temp.size(); i++)
            {
                if (temp[i].first == value)
                    return i;
            }

            throw std::runtime_error("Enum not found.");
        }

        static Type enumFromString(std::string value)
        {
            for (auto pair : pairs())
            {
                if (pair.second == value)
                    return pair.first;
            }

            throw std::runtime_error("Enum not found.");
        }
    };

}
