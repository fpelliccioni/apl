#pragma once

//NOTE(fernando)
// #include <APL/tokenizer/Token.h>

#include <memory>

//NOTE(fernando)
namespace APL::tokenizer {
class Token;
}

namespace APL::types {

//NOTE(fernando)
// using Token = APL::tokenizer::Token;


class Tokenable {
public:
    virtual std::shared_ptr<::APL::tokenizer::Token> getToken() = 0;
};

}
