#pragma once

#include <APL/tokenizer/Token.h>
#include <APL/types/Tokenable.h>
// #include <APL/types/Callable.h>
#include <APL/Sys.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types {
class Callable;
}

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace APL::errors { class Mg; }

// using namespace APL;
// using Token = APL::tokenizer::Token;
// using namespace APL::types;

namespace APL::errors {

class APLError
// : public RuntimeException
: public std::enable_shared_from_this<APLError>
{
public:
    std::shared_ptr<APL::types::Tokenable> cause;

protected:
    APLError(std::string const& msg);
    APLError(std::string const& msg, std::shared_ptr<::APL::types::Tokenable> blame);
    APLError(std::string const& msg, std::shared_ptr<::APL::types::Callable> blame, std::shared_ptr<APL::types::Tokenable> cause);


public:
    virtual void print(std::shared_ptr<Sys> s);

    virtual void println(std::shared_ptr<Sys> s, std::vector<std::shared_ptr<Mg>> &gs);

public:
    class Mg : public std::enable_shared_from_this<Mg>
    {
public:
    const std::shared_ptr<APL::tokenizer::Token> t;
    const wchar_t c;
    const std::string raw;
    int lns = 0;
    int spos = 0, epos = 0; // in the line

    Mg(std::shared_ptr<APL::tokenizer::Token> t, wchar_t c, std::string const& raw, int lns, int spos, int epos);

    static void add(std::vector<std::shared_ptr<Mg>> &l, std::shared_ptr<APL::types::Tokenable> to, wchar_t c);

    virtual bool eqSrc(std::shared_ptr<Mg> g);
    };
};
}
