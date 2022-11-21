#pragma once

#include <APL/types/arrs/ChrArr.h>
#include <APL/types/Tokenable.h>
#include <APL/errors/APLError.h>
#include <APL/Sys.h>
#include <APL/Scope.h>
#include <APL/tokenizer/types/LineTok.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/tokenizer/types/TokArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <any>
#include <utility>
#include <helpers/tangible_exception_helper.h>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL
{

    // using namespace APL::errors;
    // using namespace APL::tokenizer;
    // using namespace APL::tokenizer::types;
    // using namespace APL::types;
    // using namespace APL::types::arrs;


//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("WeakerAccess") public class Main
    class Main : public std::enable_shared_from_this<Main>
    {
  public:
      static const std::string CODEPAGE;
      static bool debug;
      static bool vind; // vector indexing
      static bool noBoxing;
      static bool quotestrings;
      static bool enclosePrimitives;
      static bool colorful;
      static const std::shared_ptr<APL::types::arrs::ChrArr> alphabet;
      static const std::shared_ptr<APL::types::arrs::ChrArr> lowercaseAlphabet;
      static const std::shared_ptr<APL::types::arrs::ChrArr> digits;
      static int printlvl;
      static const long long startingMillis = System::currentTimeMillis();
      static std::shared_ptr<Scanner> console;
      static std::shared_ptr<APL::types::Tokenable> faulty;
      static std::shared_ptr<APL::errors::APLError> lastError;
      static void main(std::vector<std::string> &args);


  public:
      class StdSys : public Sys
      {
    public:
        static const std::shared_ptr<StdSys> inst;
        void println(std::string const& s) override;
        void print(std::string const& s) override;

        void colorprint(std::string const& s, int col) override;

        void off(int code) override;

        std::string input() override;

      protected:
          std::shared_ptr<StdSys> shared_from_this()
          {
              return std::static_pointer_cast<StdSys>(Sys::shared_from_this());
          }
      };





  public:
      static std::string formatAPL(std::vector<int> &ia);
      static std::string readFile(std::string const& path);
      static std::string readFile(std::shared_ptr<Path> path);

      static std::shared_ptr<APL::types::Obj> rexec(std::shared_ptr<APL::tokenizer::types::LineTok> s, std::shared_ptr<Scope> sc);
      static std::shared_ptr<APL::types::Obj> exec(std::string const& s, std::shared_ptr<Scope> sc);
      static std::shared_ptr<APL::types::Obj> exec(std::shared_ptr<APL::tokenizer::types::LineTok> s, std::shared_ptr<Scope> sc);
      static std::shared_ptr<APL::types::Value> vexec(std::string const& s, std::shared_ptr<Scope> sc);
      static std::shared_ptr<APL::types::Value> vexec(std::shared_ptr<APL::tokenizer::types::LineTok> s, std::shared_ptr<Scope> sc);


      static void printdbg(std::shared_ptr<Scope> sc, std::vector<std::any> &args);

      static bool isBool(std::shared_ptr<APL::types::Value> a);

  public:
      enum class EType
      {
        all
      };

      class ETypeHelper
      {
      private:
          static std::vector<std::pair<EType, std::string>> pairs()
          {
              return
              {
                  {EType::all, L"all"}
              };
          }

      public:
          static std::vector<EType> values()
          {
              std::vector<EType> temp;
              for (auto pair : pairs())
              {
                  temp.push_back(pair.first);
              }
              return temp;
          }

          static std::string enumName(EType value)
          {
              for (auto pair : pairs())
              {
                  if (pair.first == value)
                      return pair.second;
              }

              throw std::runtime_error("Enum not found.");
          }

          static int ordinal(EType value)
          {
              std::vector<std::pair<EType, std::string>> temp = pairs();
              for (std::size_t i = 0; i < temp.size(); i++)
              {
                  if (temp[i].first == value)
                      return i;
              }

              throw std::runtime_error("Enum not found.");
          }

          static EType enumFromString(std::string value)
          {
              for (auto pair : pairs())
              {
                  if (pair.second == value)
                      return pair.first;
              }

              throw std::runtime_error("Enum not found.");
          }
      };



  public:
      static std::shared_ptr<APL::types::Obj> execLines(std::shared_ptr<TokArr<std::shared_ptr<APL::tokenizer::types::LineTok>>> lines, std::shared_ptr<Scope> sc);
      static bool bool_Keyword(double d);

      static bool bool_Keyword(std::shared_ptr<APL::types::Obj> v);

      static std::shared_ptr<DoubleArr> toAPL(std::vector<int> &arr);

      static std::shared_ptr<DoubleArr> toAPL(std::vector<int> &arr, std::vector<int> &sh);

      static std::shared_ptr<APL::types::arrs::ChrArr> toAPL(std::string const& s);


      static std::string repeat(std::string const& s, int l);
    };
}
