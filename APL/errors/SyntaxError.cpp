#include <APL/SyntaxError.h>

namespace APL::errors
{
    // using namespace APL::types;

    SyntaxError::SyntaxError(std::string const& s) : APLError(s)
    {
    }

    SyntaxError::SyntaxError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun) : APLError(s, fun)
    {
    }

    SyntaxError::SyntaxError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause) : APLError(s, fun, cause)
    {
    }

    void SyntaxError::must(bool b, std::string const& msg)
    {
      if (!b)
      {
          throw SyntaxError(StringHelper::wstring_to_string(msg));
      }
    }
}
