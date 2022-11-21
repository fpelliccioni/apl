#pragma once

// #include <APL/errors/NYIError.h>
// #include <APL/tokenizer/Token.h>
#include <APL/types/Tokenable.h>
#include <APL/Type.h>

#include <string>
#include <any>
#include <memory>

#include <helpers/tangible_string_helper.h>

//NOTE(fernando)
namespace APL::tokenizer {
class Token;
}

// using namespace APL;
using Token = APL::tokenizer::Token;
// // using namespace APL::types::dimensions;
// // using namespace APL::types::functions;

namespace APL::types {

class Obj
    : public std::enable_shared_from_this<Obj>
    , public Tokenable
{
public:
    std::shared_ptr<APL::tokenizer::Token> token;

    virtual bool isObj();
    virtual Type type() = 0;
    virtual bool equals(std::shared_ptr<Obj> o);

    virtual std::string humanType(bool article);

    virtual bool equals(std::any obj);

    virtual std::string name();

    virtual std::string toString();

    virtual int hashCode();

protected:
    int actualHashCode();

public:
    std::shared_ptr<APL::tokenizer::Token> getToken() override;
};

}
